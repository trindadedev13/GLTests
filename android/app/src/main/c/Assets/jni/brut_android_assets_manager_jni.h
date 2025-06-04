#ifndef BRUT_ANDROID_ASSETS_MANAGER_JNI_H
#define BRUT_ANDROID_ASSETS_MANAGER_JNI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <jni.h>

typedef struct {
  jobject o_brut_assets_manager;
  jclass c_brut_assets_manager;
  JavaVM* jvm;
} BrutAssetsManagerJNI;

typedef struct {
  int8_t* data;
  size_t size;
} Int8Array;

extern BrutAssetsManagerJNI* asmgr;

jint JNI_OnLoad(JavaVM*, void*);

JNIEXPORT void JNICALL
Java_dev_trindadedev_brut_BrutActivity_initAssets(JNIEnv*, jclass, jobject);

char* BrutAssetsManagerJNI_ReadTextFile(const char*);

Int8Array* BrutAssetsManagerJNI_ReadBinaryFile(const char*);

bool BrutAssetsManagerJNI_FileExists(const char*);

char** BrutAssetsManagerJNI_ListFiles(const char*, int*);

void BrutAssetsManagerJNI_FreeFileList(char**, int);

#ifdef __cplusplus
}
#endif

#endif