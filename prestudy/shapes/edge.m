classdef edge < handle
   properties
       su1
       su2
       index
       normal
   end
   methods
       function obj = edge(su1, su2, index, n)
           obj.su1 = su1;
           obj.su2 = su2;
           obj.index = index;
           obj.normal = n;
       end
   end
end