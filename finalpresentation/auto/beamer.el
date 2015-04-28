(TeX-add-style-hook
 "beamer"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("beamer" "presentation" "bigger")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem") ("babel" "dutch") ("caption" "font=scriptsize" "labelfont=bf") ("biblatex" "style=authoryear" "hyperref" "backref" "square" "natbib" "ibidtracker=false")))
   (add-to-list 'LaTeX-verbatim-environments-local "semiverbatim")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "beamer10"
    "inputenc"
    "fontenc"
    "fixltx2e"
    "graphicx"
    "longtable"
    "float"
    "wrapfig"
    "ulem"
    "textcomp"
    "marvosym"
    "wasysym"
    "latexsym"
    "amssymb"
    "amstext"
    "hyperref"
    "url"
    "multimedia"
    "babel"
    "caption"
    "biblatex")
   (TeX-add-symbols
    '("hiddencell" 2)
    '("aheader" 2))
   (LaTeX-add-bibliographies
    "bibliography")))

