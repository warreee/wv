(TeX-add-style-hook
 "paper"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("helvet" "scaled=.90") ("babel" "dutch")))
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
    "fig:osc_werking"
    "fig:data"
    "fig:energieverbruik_ram"
    "fig:tijdsduur_ram"
    "fig:energieverbruik_idle_vs_RAM"
    "fig:energieverbruik_antenne_uit"
    "fig:energieverbruik_cpu"
    "fig:energieverbruik_lpl"
    "fig:sweet_spot")
   (LaTeX-add-bibliographies
    "bibliography")
   (LaTeX-add-saveboxes
    "measure")))

