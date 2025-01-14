mkdir build
cd build
mkdir test
cd test
cl /EHsc ..\..\test\forward_list_client.cpp 
cl /EHsc ..\..\test\iterator_client.cpp
cl /EHsc ..\..\test\list_client.cpp
cl /EHsc ..\..\test\map_client.cpp
cl /EHsc ..\..\test\multimap_client.cpp
cl /EHsc ..\..\test\multiset_client.cpp
cl /EHsc ..\..\test\priority_queue_client.cpp
cl /EHsc ..\..\test\set_client.cpp
cl /EHsc ..\..\test\string_client.cpp
cl /EHsc ..\..\test\unordered_map_client.cpp
cl /EHsc ..\..\test\unordered_multimap_client.cpp
cl /EHsc ..\..\test\unordered_multiset_client.cpp
cl /EHsc ..\..\test\unordered_set_client.cpp
cl /EHsc ..\..\test\vector_client.cpp
del *.obj
cd ..\..