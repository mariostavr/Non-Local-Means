%VARIABLES
pictureSize = XXX
patchSize = X
rSize = pictureSize+(patchSize-1);

%ORIGINAL IMAGE VISUALISATION
oImage = fopen('Name_of_file.txt','r');
sizeOImage = [pictureSize pictureSize];
oImg = fscanf(oImage,'%f',sizeOImage);
figure('Name','ORIGINAL IMAGE');
imagesc(oImg'); axis image;
colormap gray;

%FILTERED IMAGE VISUALISATION
fImage = fopen('Filtered Image.txt','r');
sizefImage = [pictureSize pictureSize];
fImg = fscanf(fImage,'%f',sizefImage);
figure('Name','FILTERED IMAGE');
imagesc(fImg'); axis image;
colormap gray;

%RESIZED IMAGE VISUALISATION
rImage = fopen('Resized Image.txt','r');
sizerImage = [rSize rSize];
rImg = fscanf(rImage,'%f',sizerImage);
figure('Name','RESIZED IMAGE');
imagesc(rImg'); axis image;
colormap gray;
