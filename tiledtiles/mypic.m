buch = buch_outdoor;
for i = 1:192
    for n = 1:384
        if buch(i,n,1) == 255 &&  buch(i,n,2) == 255 && buch(i,n,3) == 255
            buch(i,n,2) = 0;
        end
    end
end