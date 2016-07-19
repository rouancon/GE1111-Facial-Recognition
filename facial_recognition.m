clear, clc
% Connor Rouan
% Facial Recognition
% GE1111, Prof. Love
% Final Integrated Project

% STEP G
% Read in names
txt_names = fopen('results_names.txt');
broken_names = textscan(txt_names, '%s %s'); % store temp b/c first/last names are broken apart
fclose(txt_names);
for i=1:4 %collapse names into 1D array first/last with space in between
    names{i} = strcat(broken_names{1}{i}, {' '}, broken_names{2}{i});
end

% Read in scores
txt_scores = fopen('results_scores.txt');
scores = fscanf(txt_scores, '%f');
fclose(txt_scores);

% Read in xvals
txt_xvals = fopen('results_xvals.txt');
broken_xvals = fscanf(txt_xvals, '%f');
fclose(txt_xvals);
counter = 1;
for j=1:4 %sort xvals into 2D array; 4 people, 5 vals per person (20 total)
    for k=1:5
        xvals(k,j) = broken_xvals(counter);
        counter = counter+1;
    end
end

% Read in yvals
txt_yvals = fopen('results_yvals.txt');
broken_yvals = fscanf(txt_yvals, '%f');
fclose(txt_yvals);
counter = 1;
for j=1:4 %sort xvals into 2D array; 4 people, 5 vals per person (20 total)
    for k=1:5
        yvals(k,j) = broken_yvals(counter);
        counter = counter+1;
    end
end

figure(1); %open figure
for i=1:4 %iterate for 4 graphs
    subplot(2,2,i); %write 4 graph to a figure in 2x2 formation
    [x_plot, y_plot] = separate(xvals, yvals, i); %get one set of xy data
    plot(x_plot,y_plot,'-b'); %plot data in blue
    axis([0 6 2 6]); %set constant axes
    text(1,5.5,names{i}); %write names on respective graphs
    text(1,4.8,strcat('score = ',num2str(scores(i)))); %write scores
    for c=1:5 %make 5 circles at the 5 points
        rectangle('Position',[x_plot(c)-.05 y_plot(c)-.05 .1 .1],'Curvature',[1,1],'EdgeColor','r'); % plot circle with radius .05
    end
    daspect([1,1,1]) %set axes for circles
end