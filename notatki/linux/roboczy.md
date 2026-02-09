bash -n {nazwa}
chmod +x skrypt

pipe 
obrobka tekstu - wyszukiwanie, modyfikowanie lini, przestawianie z danego zalozenia

zaszyfruj - r13

pandoc date.md -s --css=dark-style.css --highlight-style=breezedark -o date.html
pandoc combined.md -s --css=dark-style.css --syntax-highlighting=breezedark --toc --from=markdown-tex_math_dollars -o combined.html

jupyter nbconvert --to html ../archiwum/kolos1/linux.ipynb --output-dir=../bialy_motyw --output=linux.html