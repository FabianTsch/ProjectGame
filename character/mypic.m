buch = char_1;
for i = 1:128
    for n = 1:192
        if buch(i,n,1) == 255 &&  buch(i,n,2) == 255 && buch(i,n,3) == 255
            buch(i,n,2) = 0;
            buch(i,n,1) = 255;
            buch(i,n,3) = 255;
        end
    end
end