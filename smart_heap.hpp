#ifndef _SMART_HEAP_HPP
#define _SMART_HEAP_HPP

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>

class SmartHeap
{
private:
    struct SmartHeapAllocation {
        unsigned char* HeapAllocation;
        uint32_t TotalHeapSize;

        uint32_t RVAToData;
        uint32_t SizeOfData;
    };

    std::vector<SmartHeapAllocation> HeapAllocations;

    uint32_t RandomInteger(uint32_t Min, uint32_t Max)
    {
        std::random_device RandomDevice;
        std::mt19937 MTDevice(RandomDevice());
        std::uniform_real_distribution<float> Distance(Max, Min);

        return (uint32_t)Distance(MTDevice);
    }
    unsigned char RandomByte()
    {
        return (unsigned char)this->RandomInteger(0, 255);
    }

    void PopulateHeapWithFake(void* Heap, uint32_t HeapSize)
    {
        unsigned char* FakeBytesHeap = new unsigned char[HeapSize];
        memcpy(Heap, FakeBytesHeap, HeapSize);

        delete[] FakeBytesHeap;
    }

public:
    bool DestroyHeapAllocations()
    {
        for (const auto& SegmentHeap : this->HeapAllocations)
            delete[] SegmentHeap.HeapAllocation;
        return true;
    }

    std::vector<unsigned char> ReconstructHeapAllocations()
    {
        std::vector<unsigned char> ReturnVector;

        for (const auto& SegmentHeap : this->HeapAllocations)
        {
            std::vector<unsigned char> ExtractedData(SegmentHeap.SizeOfData);

            memcpy(&ExtractedData[0], SegmentHeap.HeapAllocation + SegmentHeap.RVAToData, SegmentHeap.SizeOfData);

            for (const auto& Byte : ExtractedData)
                ReturnVector.push_back(Byte);
        }

        return ReturnVector;
    }

    SmartHeap(std::vector<unsigned char> Bytes, uint32_t StoreSegments)
    {

        std::vector< std::vector<unsigned char> > Segments;
        for (uint32_t StartIter = 0; StartIter < StoreSegments; StartIter++)
        {
            std::vector<unsigned char> CurrentSegment;

            uint32_t ObjectiveStart = Segments.size();

            for (uint32_t i = ObjectiveStart; i < Bytes.size(); i += StoreSegments)
                CurrentSegment.push_back(Bytes[i]);

            Segments.push_back(CurrentSegment);
        }

        for (const auto& Segment : Segments)
        {
            uint32_t TotalHeapSize = Segment.size() * 2;

            unsigned char* SegmentHeap = new unsigned char[TotalHeapSize];

            ZeroMemory(SegmentHeap, TotalHeapSize);

            this->PopulateHeapWithFake(SegmentHeap, TotalHeapSize);

            uint32_t SmallestBound = 0, LargestBound = Segment.size();

            uint32_t DataRVA = this->RandomInteger(SmallestBound, LargestBound);

            memcpy(SegmentHeap + DataRVA, &Segment[0], Segment.size());

            this->HeapAllocations.push_back({
                SegmentHeap,
                TotalHeapSize,
                DataRVA,
                (uint32_t)Segment.size()
                });
        }
    }
};

#endif
#pragma once
#pragma once