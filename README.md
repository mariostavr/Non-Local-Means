# Google Colab Setup - Compile/Run
  USEFULL SHORTCUTS:
  1. Create a new code block: ctrl M B  
  2. Run: ctrl ENTER
  
  STEPS:
  1. Go to https://colab.research.google.com/ and Click on "New Notebook".
  2. Click on Runtime >> Change >> Hardware Accelerator GPU.
  3. Check the version of CUDA by running the command line below:
     >> !nvcc --version
![version](https://user-images.githubusercontent.com/77213227/109364442-831c5900-7897-11eb-9d7c-3bba4fc15204.PNG)
  4. Execute the given command to install a small extension to run nvcc from Notebook cells 
     (Write code in a Seperate code Block and Run that)
     >> !pip install git+git://github.com/andreinechaev/nvcc4jupyter.git
![install nvcc](https://user-images.githubusercontent.com/77213227/109364589-cbd41200-7897-11eb-9c4c-07e498fa6bf6.PNG)
  5. Load extension by running the followed command line. (Write code in a Seperate code Block and Run that)
     >> %load_ext nvcc_plugin
![extension](https://user-images.githubusercontent.com/77213227/109364687-02119180-7898-11eb-85c9-b9a69e3d73ac.PNG)
  6. Create a new code block for the code and copy/paste the code from text file "CUDA_NonLocalMeans.cu"
  7. Click on Files Icon and upload the images. (Text Files)
  
![files](https://user-images.githubusercontent.com/77213227/109365237-62550300-7899-11eb-9cd3-999c2c83618c.PNG)

  8. Adjust "pictureSize", "patchSize" and "Name_of_file"
  
![size](https://user-images.githubusercontent.com/77213227/109365079-00949900-7899-11eb-98e9-9a31fd0671ad.PNG)
![nameFIle](https://user-images.githubusercontent.com/77213227/109365082-02f6f300-7899-11eb-9bf3-b96e958d3eff.PNG)

  9. Compile/run the code. In files it will be appeared two file. "Resized Image", "Filtered Image". Download them.
 
# Visualization - Matlab
  1. Copy paste the downloaded files in the folder where the script is.
  2. Adjust "pictureSize", "patchSize" and "Name_of_file". Press Run.
![matlabScript](https://user-images.githubusercontent.com/77213227/109400000-d56c8100-794e-11eb-8d4b-9d0f7e7f6982.PNG)







