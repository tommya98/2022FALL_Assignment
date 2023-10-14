clear;
close all;


fid=fopen('usc32.raw','rb');
input_raw = fread(fid, [512, 512], 'int32');
fclose(fid);
figure;
imagesc(input_raw');colormap(gray);

fid=fopen('outfile_C.raw','rb');
outfile_C = fread(fid,  [512-15+1, 512-15+1], 'int32');
fclose(fid);
figure;
imagesc(outfile_C');colormap(gray);

fid=fopen('outfile_SIMD.raw','rb');
outfile_SIMD = fread(fid, [512-15+1, 512-15+1], 'int32');
fclose(fid);
figure;
imagesc(outfile_SIMD');colormap(gray);

