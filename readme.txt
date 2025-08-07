folders:
	- benchmarkresults: Bevat de benchmarkresults per herschrijving. bounded_negation bevat de resultaten van het originele programma zonder positive rewrite
	- facts: Dit zijn de facts waarop de benchmarks gerund worden. Nodes worden voorgesteld door een nummer, een edge is dus niet meer dan een combinatie van twee zulke nummers (een tuple)
	- output: Bevat de output van de programma's in de vorm van x,y paren die deel uitmaken van een open of gesloten driehoek.

input_generator.py: Bestandje dat gerund kan worden om inputdate in de facts folder te genereren. Hier kan men opgeven hoeveel nodes en hoeveel edges men wilt hebben.
input_generator runnen: python3 ./input_generator.py 

Een benchmark runnen doet men als volgt:
	souffle -F facts -D output -pbounded_negation bounded_negation.dl
De -p parameter achter output zet de profiler aan zodat een logfile wordt gegenereerd met de benchmarkresults met de gespecifieerde naam

Eens men een logfile heeft kan men souffleprof runnen om een mooi overzichtje te krijgen met de benchmarkresultaten
souffleprof ./benchmarkresults/bounded_negation/bounded_negation_10_nodes_100_edges.log 

https://souffle-lang.github.io/profiler



souffle --magic-transform=* --generate=transformed.cpp positive_rewrite_domain_reduction.dl -F facts -D output -ppos_rewrite.log -v
souffle --magic-transform=* positive_rewrite_domain_reduction.dl -F facts -D output -ppos_rewrite.log -v
Van 24 seconden naar 14 seconden


souffleprof ./benchmarkresults/positive_rewrite/positive_rewrite_100_nodes_2000_edges.log 
=> 1.8 min
souffleprof ./benchmarkresults/positive_rewirte_domain_reduction/positive_rewrite_domain_reduction_100_nodes_2000_edges.log
=> 24s sec
souffleprof ./pos_rewrite_with_Magic_sets_100_nodes_2000_edges.log 
=> 14 sec


source venv/bin/activate