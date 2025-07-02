Algemeen:
------------------------------------------------------------------------------------------------------------------------------------------------------

Elke dataset wordt gedefinieerd door twee parameters:
Nodes (Knopen): Het aantal unieke punten in de graaf. Een hoger aantal verhoogt exponentieel het aantal mogelijke relaties en de complexiteit.
Density (Dichtheid): De kans (tussen 0 en 1) dat er een relatie (een edge, R of S feit) bestaat tussen twee willekeurige knopen.
------------------------------------------------------------------------------------------------------------------------------------------------------


Dataset 1: data_50nodes_0p1density
Beschrijving
Dit is een kleine, relatief dichte dataset. Met 50 knopen en een dichtheid van 10% is de graaf klein genoeg om snel te verwerken, maar dicht genoeg om interessante structuren te bevatten, zoals gesloten en open driehoeken. Het aantal feiten zal rond de 245 liggen (50 * 49 * 0.1).

Unieke Kenmerken & Doel
Doel: Fungeren als een "sanity check" en basislijn.

Uniek: De hoge dichtheid in verhouding tot de grootte maakt het ideaal om de correctheid van alle programmaversies te verifiëren. De resultaten moeten snel beschikbaar zijn en kunnen eenvoudig manueel gecontroleerd worden.

Potentiële Valkuilen
Geen. Zelfs de meest inefficiënte algoritmes (zoals de niet-geoptimaliseerde herschrijving met Adom-explosie) zouden op deze dataset nog binnen een redelijke tijd moeten kunnen draaien.
------------------------------------------------------------------------------------------------------------------------------------------------------


Dataset 2: data_100nodes_0p05density
Beschrijving
Een middelgrote dataset met een gemiddelde dichtheid. Het aantal knopen is verdubbeld en de dichtheid is gehalveerd. Het aantal feiten zal rond de 495 liggen (100 * 99 * 0.05), wat ongeveer het dubbele is van de vorige dataset.

Unieke Kenmerken & Doel
Doel: Een eerste realistische test van de schaalbaarheid.

Uniek: De balans tussen grootte en dichtheid maakt dit een goede "standaard" benchmark. De performantieverschillen tussen de verschillende herschrijvingen zullen hier voor het eerst duidelijk meetbaar worden.

Potentiële Valkuilen
Inefficiënte joins beginnen hier een merkbare impact te hebben. De niet-geoptimaliseerde versie zal hier al significant trager zijn dan de geoptimaliseerde versies (of zou toch moeten).
------------------------------------------------------------------------------------------------------------------------------------------------------


Dataset 3: data_500nodes_0p02density
Beschrijving
Een grote, relatief ijle (sparse) dataset. Het aantal knopen is significant verhoogd, maar de dichtheid is verlaagd om het aantal feiten beheersbaar te houden (rond de 4990 feiten: 500 * 499 * 0.02).

Unieke Kenmerken & Doel
Doel: Het blootleggen van de combinatorische explosie.

Uniek: Deze dataset is speciaal ontworpen om het zwakke punt van de formele, niet-geoptimaliseerde herschrijving te demonstreren. De Adom-relatie bevat nu 500 elementen.

Potentiële Valkuilen
Timeout-Garantie: Dit is de dataset waar je 1_positive_rewrite_proposition_6_3_toegepast.dl programma gegarandeerd in een timeout zal gaan. De generatie van |Adom| * |Adom| = 500 * 500 = 250.000 tussenfeiten per gevonden patroon zal het systeem doen vastlopen. Dit is de perfecte dataset om de absolute noodzaak van de latere optimalisaties aan te tonen.
------------------------------------------------------------------------------------------------------------------------------------------------------


Dataset 4: data_1000nodes_0p01density
Beschrijving
Een zeer grote, zeer ijle dataset. Dit is de stresstest voor de performantie van de geoptimaliseerde programma's. Het aantal feiten is beheersbaar (rond de 9990: 1000 * 999 * 0.01), maar het zoekgebied voor de Datalog-engine is enorm.

Unieke Kenmerken & Doel
Doel: De efficiëntie van de finale, geoptimaliseerde algoritmes met elkaar vergelijken.

Uniek: Hier worden de interne optimalisaties van de Soufflé-engine zelf op de proef gesteld (bv. de keuze van de join-strategie, indexering). Kleine verschillen in de Datalog-code kunnen hier een grote impact hebben op de uitvoeringstijd.

Potentiële Valkuilen
Zelfs voor de geoptimaliseerde programma's kan de uitvoeringstijd aanzienlijk zijn. De timeout-functie kan hier ook voor geoptimaliseerde programma's in werking treden als er subtiele inefficiënties overblijven. Het is de ultieme test voor de performantie.
