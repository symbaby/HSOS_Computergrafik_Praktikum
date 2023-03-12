//
//  Model.cpp
//  ogl4
//
//  Created by Philipp Lensing on 21.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "../include/Model.h"
#include "../include/PhongShader.h"
#include <list>

float minX;
float minY;
float minZ;
float maxX;
float maxY;
float maxZ;

// Default Groesse
float scaling = 1.00f;
// Skalierfaktor
float faktor = 2.00f;

// Hilfsvariable fuer fitsize
bool check;


Model::Model() : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0) {

}

Model::Model(const char *ModelFile, bool FitSize) : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0) {
    m_FitSize = FitSize;
    bool ret = load(ModelFile);
    if (!ret)
        throw std::exception();
}

Model::~Model() {
    // TODO: Add your code (Exercise 3)
    deleteNodes(&RootNode);

    // Speicher freigeben
    delete[] pMeshes;
    delete[] pMaterials;

}

void Model::deleteNodes(Node *pNode) {
    if (!pNode)
        return;
    for (unsigned int i = 0; i < pNode->ChildCount; ++i)
        deleteNodes(&(pNode->Children[i]));
    if (pNode->ChildCount > 0)
        delete[] pNode->Children;
    if (pNode->MeshCount > 0)
        delete[] pNode->Meshes;
}

bool Model::load(const char *ModelFile, bool FitSize) {
    const aiScene *pScene = aiImportFile(ModelFile, aiProcessPreset_TargetRealtime_Fast | aiProcess_TransformUVCoords);

    if (pScene == NULL || pScene->mNumMeshes <= 0)
        return false;

    Filepath = ModelFile;
    Path = Filepath;
    size_t pos = Filepath.rfind('/');
    if (pos == std::string::npos)
        pos = Filepath.rfind('\\');
    if (pos != std::string::npos)
        Path.resize(pos + 1);

    loadMeshes(pScene, FitSize);
    loadMaterials(pScene);
    loadNodes(pScene);

    return true;
}

void Model::loadMeshes(const aiScene *pScene, bool FitSize) {
    // TODO: Add your code (Exercise 3)

    check = FitSize;
    MeshCount = pScene->mNumMeshes;
    pMeshes = new Mesh[MeshCount];

    // Axix Aligned Bounding Box
    AABB aabb(minX, minY, minZ, maxX, maxY, maxZ);

    calcBoundingBox(pScene, aabb);
    std::cout << "Num Meshes: " << MeshCount << std::endl;

    for (int i = 0; i < MeshCount; i++) {
        pMeshes[i].VB.begin();

        // Den brauchen wir fuer Textur
        pMeshes[i].MaterialIdx = pScene->mMeshes[i]->mMaterialIndex;

        for (int k = 0; k < pScene->mMeshes[i]->mNumVertices; k++) {

            // Normale
            if (pScene->mMeshes[i]->HasNormals()) {
                pMeshes[i].VB.addNormal(pScene->mMeshes[i]->mNormals[k].x,
                                        pScene->mMeshes[i]->mNormals[k].y,
                                        pScene->mMeshes[i]->mNormals[k].z);

            }

            // Texturkoordinaten
            // TODO Texuture Cords für Bump und Normal Craften
            if (pScene->mMeshes[i]->HasTextureCoords(0)) {
                pMeshes[i].VB.addTexcoord0(pScene->mMeshes[i]->mTextureCoords[0][k].x,
                                           -pScene->mMeshes[i]->mTextureCoords[0][k].y);
            }

            pMeshes[i].VB.addVertex(pScene->mMeshes[i]->mVertices[k].x * scaling,
                                    pScene->mMeshes[i]->mVertices[k].y * scaling,
                                    pScene->mMeshes[i]->mVertices[k].z * scaling);
        }
        pMeshes[i].VB.end();
    }

    for (int i = 0; i < MeshCount; i++) {
        pMeshes[i].IB.begin();

        // Dreiecke
        for (int j = 0; j < pScene->mMeshes[i]->mNumFaces; j++) {
            for (int t = 0; t < 3; t++) {
                pMeshes[i].IB.addIndex(pScene->mMeshes[i]->mFaces[j].mIndices[t]);
            }
        }
        pMeshes[i].IB.end();
    }

    std::cout << aabb.Min.X << " " << aabb.Min.Y << " " << aabb.Min.Z << " " << aabb.Max.X << " " << aabb.Max.Y << " "
              << aabb.Max.Z << std::endl;

}


void Model::loadMaterials(const aiScene *pScene) {
    // TODO: Add your code (Exercise 3)
    MaterialCount = pScene->mNumMaterials;
    pMaterials = new Material[MaterialCount];

    aiString path;

    for (int i = 0; i < MaterialCount; i++) {
        aiMaterial *aiMaterial = pScene->mMaterials[i];


        /* BRAUCHEN WIR NICHT
        // Musste abgefangen werden sonst laueft buddha nicht
        // if (AI_SUCCESS == aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path)) {
        //pMaterials[i].DiffTex = new Texture((Path + path.data).c_str());

        std::string begin;
        std::string end;
        std::string fullPath = Path + path.data;
        std::size_t delim = fullPath.find_last_of(".");
        begin = fullPath.substr(0, delim);
        end = fullPath.substr(delim);
        */

        int numTextures = pScene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE);
        if (numTextures > 0) {
            pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), path);
            std::string textureFileName = Path + path.data;
            pMaterials[i].DiffTex = Texture::LoadShared(textureFileName.c_str());
        }

        //pMaterials[i].DiffTex = Texture::LoadShared((begin + end).c_str());

        //Diffusion laden
        aiColor3D color;
        if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
            pMaterials[i].DiffColor = Color(color.r, color.g, color.b);
        }

        //Specular Color laden
        if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
            pMaterials[i].SpecColor = Color(color.r, color.g, color.b);
        }

        //Ambient Color laden
        if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
            pMaterials[i].AmbColor = Color(color.r, color.g, color.b);
        }

        //Specular exponent laden
        float exponent;
        if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_SHININESS, exponent)) {
            pMaterials[i].SpecExp = exponent;
        }
    }
}
//}

void Model::calcBoundingBox(const aiScene *pScene, AABB &Box) {
    // TODO: Add your code (Exercise 3)
    // std::cout << "Bounding Box start" << std::endl;

    for (int i = 0; i < MeshCount; i++) {
        for (int k = 0; k < pScene->mMeshes[i]->mNumVertices; k++) {
            if (pScene->mMeshes[i]->mVertices[k].x > maxX) {
                maxX = pScene->mMeshes[i]->mVertices[k].x;
            }

            if (pScene->mMeshes[i]->mVertices[k].y > maxY) {
                maxY = pScene->mMeshes[i]->mVertices[k].y;
            }

            if (pScene->mMeshes[i]->mVertices[k].z > maxZ) {
                maxZ = pScene->mMeshes[i]->mVertices[k].z;
            }

            // Min Boundries suchen
            if (pScene->mMeshes[i]->mVertices[k].x < minX) {
                minX = pScene->mMeshes[i]->mVertices[k].x;
            }

            if (pScene->mMeshes[i]->mVertices[k].y < minY) {
                minY = pScene->mMeshes[i]->mVertices[k].y;
            }

            if (pScene->mMeshes[i]->mVertices[k].z < minZ) {
                minZ = pScene->mMeshes[i]->mVertices[k].z;
            }
        }
    }

    if (check) {
        scaling = faktor / (maxZ - minZ);
    }

    // Wieso kann man die uebergebene Box nicht aendern?
    // Werte wurden nie uebernommen????
    // fragen

    Box.Max.X = maxX * scaling;
    Box.Max.Y = maxY * scaling;
    Box.Max.Z = maxZ * scaling;

    Box.Min.X = minX * scaling;
    Box.Min.Y = minY * scaling;
    Box.Min.Z = minZ * scaling;

}


void Model::loadNodes(const aiScene *pScene) {
    deleteNodes(&RootNode);
    copyNodesRecursive(pScene->mRootNode, &RootNode);
}

void Model::copyNodesRecursive(const aiNode *paiNode, Node *pNode) {
    pNode->Name = paiNode->mName.C_Str();
    pNode->Trans = convert(paiNode->mTransformation);

    if (paiNode->mNumMeshes > 0) {
        pNode->MeshCount = paiNode->mNumMeshes;
        pNode->Meshes = new int[pNode->MeshCount];
        for (unsigned int i = 0; i < pNode->MeshCount; ++i)
            pNode->Meshes[i] = (int) paiNode->mMeshes[i];
    }

    if (paiNode->mNumChildren <= 0)
        return;

    pNode->ChildCount = paiNode->mNumChildren;
    pNode->Children = new Node[pNode->ChildCount];
    for (unsigned int i = 0; i < paiNode->mNumChildren; ++i) {
        copyNodesRecursive(paiNode->mChildren[i], &(pNode->Children[i]));
        pNode->Children[i].Parent = pNode;
    }
}

void Model::applyMaterial(unsigned int index) {
    if (index >= MaterialCount)
        return;

    PhongShader *pPhong = dynamic_cast<PhongShader *>(shader());
    if (!pPhong) {
        std::cout
                << "Model::applyMaterial(): WARNING Invalid shader-type. Please apply PhongShader for rendering models.\n";
        return;
    }

    Material *pMat = &pMaterials[index];
    pPhong->ambientColor(pMat->AmbColor);
    pPhong->diffuseColor(pMat->DiffColor);
    pPhong->specularExp(pMat->SpecExp);
    pPhong->specularColor(pMat->SpecColor);
    pPhong->diffuseTexture(pMat->DiffTex);
}

void Model::draw(const BaseCamera &Cam) {
    if (!pShader) {
        std::cout << "BaseModel::draw() no shader found" << std::endl;
        return;
    }
    pShader->modelTransform(transform());

    std::list<Node *> DrawNodes;
    DrawNodes.push_back(&RootNode);

    while (!DrawNodes.empty()) {
        Node *pNode = DrawNodes.front();
        Matrix GlobalTransform;

        if (pNode->Parent != NULL)
            pNode->GlobalTrans = pNode->Parent->GlobalTrans * pNode->Trans;
        else
            pNode->GlobalTrans = transform() * pNode->Trans;

        pShader->modelTransform(pNode->GlobalTrans);

        for (unsigned int i = 0; i < pNode->MeshCount; ++i) {
            Mesh &mesh = pMeshes[pNode->Meshes[i]];
            mesh.VB.activate();
            mesh.IB.activate();
            applyMaterial(mesh.MaterialIdx);
            pShader->activate(Cam);
            glDrawElements(GL_TRIANGLES, mesh.IB.indexCount(), mesh.IB.indexFormat(), 0);
            mesh.IB.deactivate();
            mesh.VB.deactivate();
        }
        for (unsigned int i = 0; i < pNode->ChildCount; ++i)
            DrawNodes.push_back(&(pNode->Children[i]));

        DrawNodes.pop_front();
    }
}

Matrix Model::convert(const aiMatrix4x4 &m) {
    return Matrix(m.a1, m.a2, m.a3, m.a4,
                  m.b1, m.b2, m.b3, m.b4,
                  m.c1, m.c2, m.c3, m.c4,
                  m.d1, m.d2, m.d3, m.d4);
}




