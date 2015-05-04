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
    "fig:meetopstelling"
    "fig:energieverbruik_ram"
    "fig:tijdsduur_ram"
    "fig:energieverbruik_low_power"
    "fig:energieverbruik_antenne_uit"
    "fig:energieverbruik_cpu"
    "fig:voorbeeld_topologie"
    "fig:sweet_spot")
   (LaTeX-add-bibliographies
    "bibliography")))

