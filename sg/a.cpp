首先定义mex(minimal excludant)运算，这是施加于一个集合的运算，表示最小的不属于这个集合的非负整数。例如mex{0,1,2,4}=3、mex{2,3,5}=0、mex{}=0。
对于一个给定的有向无环图，定义关于图的每个顶点的Sprague-Grundy函数g如下：g(x)=mex{ g(y) | y是x的后继 }。
