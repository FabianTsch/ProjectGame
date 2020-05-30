
k = 1;
j = 1;

for i  = 1:8
    for n = 1:12
        a = monster(k:k+15,j:15+j,:);
        filename = "tile_" + num2str(i) + "_" + num2str(n)+".bmp";
        imwrite(a,filename)
        j = j+16;
    end
    j = 1;
    k = k +16;
end
