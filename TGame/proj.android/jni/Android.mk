LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MainScene.cpp \
		   ../../Classes/Background.cpp \
		   ../../Classes/Blood.cpp \
		   ../../Classes/Bullet.cpp \
		   ../../Classes/GameOverLayer.cpp \
		   ../../Classes/Gun.cpp \
		   ../../Classes/Monster.cpp \
		   ../../Classes/PauseLayer.cpp
		   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
