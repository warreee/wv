(TeX-add-style-hook
 "paper"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "11pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("xcolor" "table") ("helvet" "scaled=.90") ("babel" "dutch")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art11"
    "xcolor"
    "ijcai11"
    "lipsum"
    "mathptmx"
    "helvet"
    "courier"
    "latexsym"
    "environ"
    "listings"
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
    "fig:pin_flip_code"
    "fig:energieverbruik_ram"
    "fig:tijdsduur_ram"
    "fig:energieverbruik_idle_vs_RAM"
    "fig:energieverbruik_antenne_uit"
    "fig:energieverbruik_cpu"
    "fig:energieverbruik_lpl"
    "fig:energieverbruik_ant"
    "tab:toetsing"
    "fig:sweet_spot")
   (LaTeX-add-bibliographies
    "bibliography")
   (LaTeX-add-saveboxes
    "measure")))

