classdef support < handle
   properties
       p1
       p2
       p3
   end
   methods
       function obj = support(s1, s2, d)
           obj.p1 = s1.getFarthestPointInDirection(d);
           obj.p2 = s2.getFarthestPointInDirection(-d);
           obj.p3 = obj.p1 - obj.p2;
           %plot([obj.p1(1) obj.p2(1)], [obj.p1(2) obj.p2(2)]);
       end
   end
end