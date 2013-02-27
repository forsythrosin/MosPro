function plotVector(point, vector, color)
    plot([point(1) point(1) + vector(1)], [point(2) point(2) + vector(2)], color,'LineWidth', 2);
end

