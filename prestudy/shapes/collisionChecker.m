classdef collisionChecker < handle
    properties (GetAccess=private)
        simplex
        d
    end
    methods
        function collision = checkCollision(obj, s1, s2)
            collision = false;
            
            if( s1.movable || s2.movable )
                obj.simplex = [];

                obj.d = s2.p - s1.p;
                obj.simplex = [obj.simplex support(s1, s2, obj.d)];
                obj.d = -obj.d;

                while true
                    obj.simplex = [obj.simplex support(s1, s2, obj.d)];
                    obj.d = obj.d / norm(obj.d);
                    if obj.simplex(end).p3' * obj.d < 0
                        collision = false;
                        break;
                    else
                        if obj.containsOrigin()
                            collision = true;
                            [t1, t2, point, penetrationVector, a, b] = obj.epa(s1, s2);
                            obj.collisionRespond(t1, t2, point, penetrationVector, a, b);
                            break;
                        end
                    end
                end %end of while
            end
            
        end %end of checkCollision
        
        function contains = containsOrigin(obj) 
            contains = false;
            a = obj.simplex(end).p3;
            ao = -a;
            
            if length(obj.simplex) == 3
                b = obj.simplex(2).p3;
                c = obj.simplex(1).p3;
                ab = b - a;
                ac = c - a;
                
                %ac*ab*ab
                abPerp = ab*(ac'*ab) - ac * (ab'*ab);
                %ab*ac*ac
                acPerp = ac*(ab'*ac) - ab * (ac'*ac);
                
                if abPerp'*ao > 0
                    obj.simplex(1) = [];
                    obj.d = abPerp;
                elseif acPerp'*ao > 0
                    obj.simplex(2) = [];
                    obj.d = acPerp;
                else             
                    contains = true;
                end
            else
                b = obj.simplex(1).p3;
                ab = b - a;
                abPerp = ([-ab(2) ab(1)]*ao)*[-ab(2) ab(1)]';
                
                %abPerp = tripleProduct(ab, ao, ab);
                %abPerp = ab*(ac'*ab) - ac * (ab'*ab);
                %abPerp = ...
                obj.d = abPerp;
            end
        end
        
        
        function [t1, t2, point, penetrationVector, a, b] = epa(obj, s1, s2)
            tolerance = 0.00001;
            
            while true
                e = obj.findClosestEdge();
                p = support(s1, s2, e.normal);
                dist = p.p3'*(e.normal/norm(e.normal));
                if (dist - norm(e.normal) < tolerance) 
                    penetrationVector = e.normal;
                    
                    if norm(e.su1.p1 - e.su2.p1) < tolerance
                        point = e.su1.p1; %( = e.su2.p1)
                        a = e.su1.p2;
                        b = e.su2.p2;
                        c = (b - a);
                        cOrt = [-c(2) c(1)]';
                        if (dot(cOrt,penetrationVector) < 0)
                           temp = a;
                           a = b;
                           b = temp;
                        end
                        penetrationVector = -penetrationVector;
                        t1 = s1;
                        t2 = s2;
                    else
                        point = e.su1.p2; %( = e.su2.p2)
                        t1 = s2;
                        t2 = s1;
                        a = e.su1.p1;
                        b = e.su2.p1;
                        c = (b - a);
                        cOrt = [-c(2) c(1)]';
                        if (dot(cOrt,penetrationVector) < 0)
                           temp = a;
                           a = b;
                           b = temp;
                        end
                    end
                    %plot([point(1) point(1)+penetrationVector(1)], [point(2) point(2)+penetrationVector(2)], 'k');
                    break;
                else
                    before = obj.simplex(1: e.index - 1);
                    after = obj.simplex(e.index : end);
                    obj.simplex = [before p after];
                end
            end
            
        end
        
        
        function closest = findClosestEdge(obj)
            for i = 1:length(obj.simplex)
                j = i + 1;
                
                if (j > length(obj.simplex))
                    j = 1;
                end
                
                a = obj.simplex(i);
                b = obj.simplex(j);
                e = b.p3 - a.p3;
                
                e = e / norm(e);
                
                n = ([-e(2) e(1)]*a.p3)*[-e(2) e(1)]';
                
                
                if (i == 1 || norm(n) < norm(closest.normal))
                    closest = edge(a, b, j, n);
                end
            end
        end
        
        
        function collisionRespond(obj, s1, s2, point, penetrationVector, a, b)
            e = 0.5;
            m1 = s1.getMass();
            i1 = s1.getInertia();

            m2 = s2.getMass();
            i2 = s2.getInertia();
            
             
            

            %plot(point(1), point(2), 'k*');
            %plot(s1.p(1), s1.p(2), 'k*');
            
%             penetrationVector = penetrationVector * 1;
            
            if (~s1.movable)
                inverseInertia = 1 / (1/m2 + 1/i2);
                lm1 = 0;
                lm2 = 1/m2 * inverseInertia;
%                 am1 = 0;
%                 am2 = 1/i2 * inverseInertia;
            elseif (~s2.movable)
                inverseInertia = 1 / (1/m1 + 1/i1);
                lm1 = 1/m1 * inverseInertia;
                lm2 = 0;
%                 am1 = 1/i1 * inverseInertia;
%                 am2 = 0;
                
            else
                inverseInertia = 1 / (1/m1 + 1/m2 + 1/i1 + 1/i2);
                lm1 = 1/m1 * inverseInertia;
                lm2 = 1/m2 * inverseInertia;
%                 am1 = 1/i1 * inverseInertia;
%                 am2 = 1/i2 * inverseInertia;
            end
            
            %this is ett jävligt dåligt hack
%             while abs(lm1 + lm2) < 0.8
%                 xlabel('needed elongation');
%                 lm1 = lm1 * 1.01;
%                 lm2 = lm2 * 1.01;
%             end
            
            r1 = point - s1.p;
            r1Ort = [-r1(2) r1(1)]'; %r1/r2 must not be normalized!
            r2 = point - s2.p;
            r2Ort = [-r2(2) r2(1)]';
            
            rotDir = sign(r1Ort' * penetrationVector);
            lm1 = penetrationVector * lm1;
            lm2 = - penetrationVector * lm2;
            
%             am = am1 + am2;
            a = a + lm2;
            b = b + lm2;
            
%             plotVector(point, lm1, 'r');
%             plotVector(point, lm2, 'b');
            
%             plotVector(a, b-a, 'r');
            
%             fprintf('%s ligger i %s\n', s1.color, s2.color);
%             s1.plot();
%             hold on;
%             s2.plot();
%             plotVector(point, penetrationVector, 'b');

            [theta1 point] = findClosestRotationAngle(a, b, penetrationVector, s1.p + lm1, r1);
            theta2 = 0;
            
            if (s1.movable)
                s1.teleport(lm1, theta1);
            end
            if (s2.movable)
                s2.teleport(lm2, theta2);
            end
%             pause();
%             s1.plot();
%             s2.plot();
            
            %plot(point(1), point(2), 'r*');
            if (abs(theta1) > (pi/2))
                fprintf('wrong rotation angle!\n');
                pause();
            end
            
            r1 = point - s1.p;
            r1Ort = [-r1(2) r1(1)]'; %r1/r2 must not be normalized!
            r2 = point - s2.p;
            r2Ort = [-r2(2) r2(1)]';
            
            v1 = s1.v + s1.w * r1Ort;
            v2 = s2.v + s2.w * r2Ort;
            
%             plotVector(point, v1*100, 'b');
%             plotVector(point, v2*100, 'r');            
            
            n = penetrationVector/norm(penetrationVector);
            vr = v1 - v2;
            
                        
            if (norm(vr) < 0.1)
                e = 0;
            end
            
            % remove accelerated velocity
%             velocityFromAcc = s1.gravity' * n;
%             velocityFromAcc = velocityFromAcc - s2.gravity' * n;
%             deltaVelocity = norm(vr) - e * (-norm(vr) - velocityFromAcc);
            
            if ((penetrationVector' * vr) < 0)
                %friction
                mu = 1;
                if s1.color == 'b'
                    mu = 0;
                end
                t =[-n(2) n(1)]';
                t = -sign(vr' * t) * t;
                
                if (~s1.movable)
                    jr = -(1 + e)*vr' * n / (1/m2 + 1/i2 * (n' * r2Ort)^2);
                    j = abs(jr) *n ;
                    
                    fjr = abs(vr' * t)/ (1/m2 + 1/i2 * (t' * r2Ort)^2);
                    fj = mu * fjr * t;
                    
                    s2.impulse(point, -fj-j);
                elseif (~s2.movable)
                    jr = -(1 + e)*vr' * n / (1/m1 + 1/i1 * (n' * r1Ort)^2);
                    j = abs(jr) * n;
                    
                    fjr = abs(vr' * t)/ (1/m1 + 1/i1 * (t' * r1Ort)^2);
                    fj = mu * fjr * t;
                   
                    s1.impulse(point, fj + j);
                else
                    jr = -(1 + e)*vr' * n / (1/m1 + 1/m2 + 1/i1 * (n' * r1Ort)^2 + 1/i2 * (n' * r2Ort)^2);
                    j = abs(jr) * n;
                    
                    fjr = abs(vr' * t)/ (1/m1 + 1/m2 + 1/i1 * (t' * r1Ort)^2 + 1/i2 * (t' * r2Ort)^2);
                    fj = mu * fjr * t;
                    
                    s1.impulse(point, fj+j);
                    s2.impulse(point, -fj-j);
                end
            end
        end
        
    end %end of methods  
end %end of classdef