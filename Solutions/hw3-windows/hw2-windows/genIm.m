im_file = load('im.txt');
counter = 1;
for i = 1:480
    for j = 1:640
        for k = 1:3
            im_mat(i,j,k) = double(im_file(counter,k));
        end
        counter = counter + 1;
    end
end
imshow(im_mat)

    
    