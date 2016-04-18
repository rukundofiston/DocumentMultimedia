# Fiston RUKUNDO
# Projet:
##http://mrim.imag.fr/GINF53C4/PROJET/
##http://mrim.imag.fr/GINF53C4/COURS/

#1# Compilation :
cc rdjpeg.c read_image.c -o read_image

#1.1# Execution sur une image
./read_image http://mrim.imag.fr/voc10/images/2008_000035.jpg

#2# Programme pour générer un fichier de vecteurs .svm "neutre" pour train et val
./script_generation_histo train/urls.txt > train/svm/color.svm

./script_generation_histo val/urls.txt > val/svm/color.svm

#3# Générer une fusion histogramme/annotations pour un concept
./script_collapse_histo_ann train/svm/color.svm train/ann/aeroplane.ann > train/svm/color_aeroplane.svm

#4# Générer un model pour un concept :
./script_generation_model color_aeroplane

#5# Générer tous les models pour tous les concepts
./script_generation_models

#6# Générer tous les fichiers predics pour tous les concepts (val)
./script_generation_predicts

#7# Générer un fichier .top
./script_generation_top val/ann/aeroplane.ann val/out/color_aeroplane.out > val/top/color_aeroplane.top

#8# Générer tous les fichiers .top :
./script_generation_tops

#9# Générer le fichier color_all.top (Fusioner de tous les fichiers tops)
cat val/top/* > val/top/color_all.top

#10# Faire trec_eval:
./script_trec_eval > val/eval.txt

-Puis presenter un tableau des valeurs trouvé-

#11# Cleaning SIFT of a given file
./script_clean_sift 2008_000070.sift

#12# Cleaning SIFT of all files:
./script_clean_all_sift

#13# Create a sample file samples.txt
cat train/sift/* > samples.txt

#14# Générer de centers256.txt avec kmeans_clustering.R
R --slave --no-save --no-restore --no-environ --args ./samples.txt 256 ./centers256.txt 10 < libsvm/kmeans_clustering.R

#15# Mapping de train
./libsvm/process_1nn_sift_train.sh

#16# Mapping de val
./libsvm/process_1nn_sift_val.sh

#17# Génération des histogrammes pour les sift
./script_generation_histo_sift

#18# Fusionner les fichier générer dans un seul fichier sift.svm (train et eval)
./script_generation_sift_svm
cat train/histo_sift_svm/* > train/histo_sift_svm/sift.svm
cat val/histo_sift_svm/* > val/histo_sift_svm/sift.svm


#19# Génération des models et predicts pour tous les sift 
./script_generation_models_sift

#20# Génération des predicts pour tous les sift 
./script_generation_predicts_sift

#21# Générer des fichiers des .top pour les sift
./script_generation_tops_sift

#22# Fusioner tous les fichiers .top dans un seul fichier all.top pour les sift :
cat val/top_sift/* > val/top_sift/color_all.top

#23# Évaluation pour les sift :
./script_trac_eval_sift > val/eval_sift.txt

#24# Fusion tardive et évaluation