(TeX-add-style-hook
 "paper"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("babel" "dutch")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "ijcai11"
    "lipsum"
    "times"
    "latexsym"
    "todonotes"
    "amsmath"
    "babel")
   (LaTeX-add-labels
    "fig:meetopstelling")
   (LaTeX-add-bibliographies
    "bibliography")))

