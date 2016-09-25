//
//  _   _         ______    _ _ _   _             _ _ _
// | \ | |       |  ____|  | (_) | (_)           | | | |
// |  \| | ___   | |__   __| |_| |_ _ _ __   __ _| | | |
// | . ` |/ _ \  |  __| / _` | | __| | '_ \ / _` | | | |
// | |\  | (_) | | |___| (_| | | |_| | | | | (_| |_|_|_|
// |_| \_|\___/  |______\__,_|_|\__|_|_| |_|\__, (_|_|_)
//                                           __/ |
//                                          |___/
// 
// This file is auto-generated. Do not edit manually
// 
// Copyright 2016 Automatak LLC
// 
// Automatak LLC (www.automatak.com) licenses this file
// to you under the the Apache License Version 2.0 (the "License"):
// 
// http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "JNILinkLayerConfig.h"

#include "JNI.h"
#include <assert.h>

namespace jni
{
    bool LinkLayerConfig::init(JNIEnv* env)
    {

        this->clazz = env->FindClass("Lcom/automatak/dnp3/LinkLayerConfig;");
        if(!this->clazz) return false;

        this->isMasterField = env->GetFieldID(this->clazz, "isMaster", "Z");
        if(!this->isMasterField) return false;

        this->useConfirmsField = env->GetFieldID(this->clazz, "useConfirms", "Z");
        if(!this->useConfirmsField) return false;

        this->numRetryField = env->GetFieldID(this->clazz, "numRetry", "I");
        if(!this->numRetryField) return false;

        this->localAddrField = env->GetFieldID(this->clazz, "localAddr", "I");
        if(!this->localAddrField) return false;

        this->remoteAddrField = env->GetFieldID(this->clazz, "remoteAddr", "I");
        if(!this->remoteAddrField) return false;

        this->responseTimeoutField = env->GetFieldID(this->clazz, "responseTimeout", "Ljava/time/Duration;");
        if(!this->responseTimeoutField) return false;

        this->keepAliveTimeoutField = env->GetFieldID(this->clazz, "keepAliveTimeout", "Ljava/time/Duration;");
        if(!this->keepAliveTimeoutField) return false;

        return true;
    }

    jboolean LinkLayerConfig::getisMaster(JNIEnv* env, jobject instance)
    {
        return env->GetBooleanField(instance, this->isMasterField);
    }

    jboolean LinkLayerConfig::getuseConfirms(JNIEnv* env, jobject instance)
    {
        return env->GetBooleanField(instance, this->useConfirmsField);
    }

    jint LinkLayerConfig::getnumRetry(JNIEnv* env, jobject instance)
    {
        return env->GetIntField(instance, this->numRetryField);
    }

    jint LinkLayerConfig::getlocalAddr(JNIEnv* env, jobject instance)
    {
        return env->GetIntField(instance, this->localAddrField);
    }

    jint LinkLayerConfig::getremoteAddr(JNIEnv* env, jobject instance)
    {
        return env->GetIntField(instance, this->remoteAddrField);
    }

    jobject LinkLayerConfig::getresponseTimeout(JNIEnv* env, jobject instance)
    {
        return env->GetObjectField(instance, this->responseTimeoutField);
    }

    jobject LinkLayerConfig::getkeepAliveTimeout(JNIEnv* env, jobject instance)
    {
        return env->GetObjectField(instance, this->keepAliveTimeoutField);
    }
}
