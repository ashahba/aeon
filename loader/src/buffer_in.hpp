/*
 Copyright 2015 Nervana Systems Inc.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#pragma once

#include <assert.h>
#if HAS_GPU
#include <cuda.h>
#endif

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <iostream>

/* Buffer
 *
 * Buffer contains an ordered list of items in contiguous memory.  The
 * position of each item in the memory is recorded in _items and the
 * length of each item is stored in _lens.
 */
class buffer_in {
public:
    explicit buffer_in(int size, bool pinned = false);
    buffer_in(char* data, int size);
    virtual ~buffer_in();

    void read(std::istream& is, int size);
    void read(const char* src, int size);
    void reset();
    char* getItem(int index, int& len);

    void dump();
    void shuffle(uint seed);

    int getItemCount();
    uint getSize();

private:
    buffer_in() = delete;
    char* alloc();
    void dealloc(char* data);
    void resize(int inc);

    uint getLevel();
    void resizeIfNeeded(int inc);

    void pushItem(int len);
    char* getCurrent();

public:
    char*                       _data;
    uint                        _size;

protected:
    char*                       _cur;
    int                         _idx;
    std::vector<int>            _items;
    std::vector<int>            _lens;
    bool                        _alloc;
    bool                        _pinned;
};

class buffer_in_array {
public:
    buffer_in_array(std::initializer_list<buffer_in*> list) : data(list) {}

    buffer_in* operator[](int i) { return data[i]; }
    size_t size() const { return data.size(); }

private:
    std::vector<buffer_in*>    data;
};