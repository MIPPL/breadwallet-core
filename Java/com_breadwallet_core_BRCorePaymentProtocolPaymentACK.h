/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_breadwallet_core_BRCorePaymentProtocolPaymentACK */

#ifndef _Included_com_breadwallet_core_BRCorePaymentProtocolPaymentACK
#define _Included_com_breadwallet_core_BRCorePaymentProtocolPaymentACK
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    getCustomerMemo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_getCustomerMemo
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    getMerchantData
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_getMerchantData
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    getTransactions
 * Signature: ()[Lcom/bitradiowallet/core/BRCoreTransaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_getTransactions
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    getRefundTo
 * Signature: ()[Lcom/bitradiowallet/core/BRCoreTransactionOutput;
 */
JNIEXPORT jobjectArray JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_getRefundTo
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    getMerchantMemo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_getMerchantMemo
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    createPaymentProtocolPaymentACK
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_createPaymentProtocolPaymentACK
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    serialize
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_serialize
  (JNIEnv *, jobject);

/*
 * Class:     com_breadwallet_core_BRCorePaymentProtocolPaymentACK
 * Method:    disposeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_breadwallet_core_BRCorePaymentProtocolPaymentACK_disposeNative
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
