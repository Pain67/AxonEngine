#ifndef AXONENGINE_SERIALIZATION_H
#define AXONENGINE_SERIALIZATION_H


#include <stdlib.h>
#include <stdint.h>
#include "../AxonUtility.h"

#define TAG_T uint16_t

// Define alias for uint64_t to be used instead of size_t
//  as size_t may have different size on different machines (i.e. x86 vs x64)
typedef uint64_t size64_t;

/**
* Creates serialized string from data given
* 
* @param data - data to serialize
* @param size - actual data size, bytes
* @param tag - message footer with utility tags
* @param[out] totalSize - will contain total serialized data size, bytes
* @returns serialized message - pointer to char array
*/
AXON_DECLSPEC char* serialize(const char* /* data */, size64_t /* size */, TAG_T /* tag */, size64_t* /* totalSize */);

/**
* @param serialized - raw data
* @param size - actual data size, bytes
* @param deserialized - will contain deserialized message, dealloc will be needed
* @param actualSize - will contain deserialized data size, bytes
* @param tag - will contain deserialized message footer
* @returns 0 or error code
*/
AXON_DECLSPEC uint8_t deserialize(const char* /* serialized */ , size64_t /* size */, void** /* deserialized */, size64_t* /* actualSize */, TAG_T* /* tag */);

#endif	// AXONENGINE_SERIALIZATION_H
