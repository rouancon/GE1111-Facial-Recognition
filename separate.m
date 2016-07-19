% Connor Rouan
% Facial Recognition
% GE1111, Prof. Love
% Final Integrated Project
% *** Function File ***

function [plot_x, plot_y]=separate(x_vals, y_vals, num)
    for i=1:5
        plot_x(i) = x_vals(i,num);
        plot_y(i) = y_vals(i,num);
    end
    plot_x(6) = x_vals(1,num); % connect last point back to first
    plot_y(6) = y_vals(1,num);
end