buch = tileset_wesley;
for i = 1:896
    for n = 1:832
        if buch(i,n,1) == 247 &&  buch(i,n,2) == 247 && buch(i,n,3) == 247
            buch(i,n,2) = 0;
            buch(i,n,1) = 255;
            buch(i,n,3) = 255;
        end
    end
end