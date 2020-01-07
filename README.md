# PHASH
## Description
A set of utilities for percetual image hashing and dublicate finding.

### GUI
 - dup-viewer
 - image-viewer
 - phash-gui

### CLI
   - phash
   
  ## CLI Usage
### Usage: `phash [options]` 

### Optional arguments:  
 - `-h --help`               show this help message and exit  
 - `-i --input`              Specify single input image file or directory[Required]  
 - `-o --output`             Specify output directory[Required]   
 - `-d --duplicates`         Specify single input image file to searh for duplicates in input directory   
 - `-h --hash`               Specify one hash type from [simple, median, diff, cosine, grad][Required]   
 - `-et --error_type`        Specify one error type from [ber, mer]   
 - `-r --resolution`         Specify resolution base   
 - `-e --error`              supply error rate (0...1], default is 0.17  
 - `-dst --distance`         supply distance [1...), no default. If specified then preffered over error rate. Used for HENGINE only.   
 - `-nhe --no_hengine`       disables hengine, requires `--error_type`  
 - `--force`                 froce rehash of all files   
 - `--get_path`              output path to dup file for given parameters  
 - `-p --profile`            output times to shell  
 - `--save`                  save resized grayscale images   
 - `--out_cmd`               output duplicates to shell instead of file  

### Output file path scheme
`{output}/{image_parent_path}/{hash}/r_{resolution}x{computed_resolution}/{filename}{ext}`  

Where:
 - `{output}` is specified by passing `-o --output` arg  
 - `{image_parent_path}` is a path to image relative to `-i --input`
 - `{hash}` is `-h --hash`
 - `{resolution}` is `-r --resolution`
 - `{computed_resolution}` is the resolution computed internally based on hash algorithm. Can differ from `{resolution}`.
 - `{filename}` is the name of file wich is hashed or is the base for finding duplicates.
 - `{ext}` is either `.hash` for hash file or `.dup` for file containing paths to duplicate images

## GUI Usage
All GUI apps expect input folder to be `./in` and output folder to be `./out`.
### dup-viewer
Shows a list of all files (`.dup`) containing duplicate lists.
Shows all duplicate images for selected file.  
To match input image and output file either use `--get_path` or manually compose path using given diplicate file path scheme.
![dup](https://user-images.githubusercontent.com/8377469/71915117-c0012a00-3183-11ea-83e7-96c9d6cbcbf5.PNG)
### image-viewer
Simple utility to list and view all image files in `./in`
![image](https://user-images.githubusercontent.com/8377469/71915199-e9ba5100-3183-11ea-9f67-03ceb90570a9.png)
### phash-gui
GUI that uses `phash` and allows to specify most parameters.
![image](https://user-images.githubusercontent.com/8377469/71917103-fe98e380-3187-11ea-9d65-2f2b063ccc04.png)
`Note: Does not work on some windows versions cause unknown. Not recomended to use for now.`
