//
//  RingBuffer.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-15.
//
//

#include "RingBuffer.h"

template <typename T>
RingBuffer<T>::RingBuffer(int size) {
    _data = new T[size];
    memset( _data, 0, size * sizeof(T));
    _size = size;
    _readPtr = 0;
    _writePtr = 0;
    _writeSamplesAvail = size;
}

template <typename T>
RingBuffer<T>::~RingBuffer() {
    delete[] _data;
}

// Set all data to 0 and flag buffer as empty.
template <typename T>
bool RingBuffer<T>::Empty() {
    memset( _data, 0, _size * sizeof(T));
    _readPtr = 0;
    _writePtr = 0;
    _writeSamplesAvail = _size;
    return true;
}

template <typename T>
int RingBuffer<T>::Read(T * dataPtr, int numSamples) {
    
    // If there's nothing to read or no data available, then we can't read anything.
    if( dataPtr == 0 || numSamples <= 0 || _writeSamplesAvail == _size ){
        return 0;
    }
    
    int readBytesAvail = _size - _writeSamplesAvail;
    
    // Cap our read at the number of bytes available to be read.
    if( numSamples > readBytesAvail ){
        numSamples = readBytesAvail;
    }
    
    // Simultaneously keep track of how many bytes we've read and our position in the outgoing buffer
    if(numSamples > _size - _readPtr){
        int len = _size-_readPtr;
        memcpy(dataPtr, _data+_readPtr, len * sizeof(T));
        memcpy(dataPtr+len, _data, (numSamples-len) * sizeof(T));
    } else {
        memcpy(dataPtr, _data+_readPtr, numSamples * sizeof(T));
    }
    
    _readPtr = (_readPtr + numSamples) % _size;
    _writeSamplesAvail += numSamples;
    
    return numSamples;
}

// Write to the ring buffer. Do not overwrite data that has not yet
// been read.
template <typename T>
int RingBuffer<T>::Write(T * dataPtr, int numSamples) {
    // If there's nothing to write or no room available, we can't write anything.
    if( dataPtr == 0 || numSamples <= 0 || _writeSamplesAvail == 0 ){
        return 0;
    }
    
    // Cap our write at the number of bytes available to be written.
    if( numSamples > _writeSamplesAvail ){
        numSamples = _writeSamplesAvail;
    }
    
    // Simultaneously keep track of how many bytes we've written and our position in the incoming buffer
    if(numSamples > _size - _writePtr){
        int len = _size-_writePtr;
        memcpy(_data+_writePtr, dataPtr, len * sizeof(T));
        memcpy(_data, dataPtr+len, (numSamples-len) * sizeof(T));
    } else {
        memcpy(_data+_writePtr, dataPtr, numSamples * sizeof(T));
    }
    
    _writePtr = (_writePtr + numSamples) % _size;
    _writeSamplesAvail -= numSamples;
    
    return numSamples;
}

template <typename T>
int RingBuffer<T>::GetSize() {
    return _size;
}

template <typename T>
int RingBuffer<T>::GetWriteAvail() {
    return _writeSamplesAvail;
}

template <typename T>
int RingBuffer<T>::GetReadAvail() {
    return _size - _writeSamplesAvail;
}