mkdir build
cd build
mkdir graph
cd graph
cl /EHsc ..\..\GraphUsingList\graph_list.cpp
cl /EHsc ..\..\GraphUsingSet\graph_set.cpp
cl /EHsc ..\..\GraphUsingUnorderedSet\graph_unordered_set.cpp
del *.obj
cd ..\..