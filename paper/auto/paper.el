(TeX-add-style-hook
 "paper"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("helvet" "scaled=.90") ("babel" "dutch")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "ijcai11"
    "lipsum"
    "mathptmx"
    "helvet"
    "courier"
    "latexsym"
    "environ"
    "todonotes"
    "hyperref"
    "amsmath"
    "float"
    "graphicx"
    "babel"
    "pgfplots")
   (TeX-add-symbols
    "tikzscale")
   (LaTeX-add-labels
    "fig:meetopstelling"
    "fig:energieverbruik_ram"
    "fig:tijdsduur_ram"
    "fig:energieverbruik_idle_vs_RAM"
    "fig:energieverbruik_antenne_uit"
    "fig:energieverbruik_cpu"
    "fig:energieverbruik_lpl")
   (LaTeX-add-bibliographies
    "bibliography")
   (LaTeX-add-saveboxes
    "measure")))

