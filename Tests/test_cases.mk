#
# Adendum file listing test cases for testing
# and benchmarking graph coloring algorithms

TESTPATH=Tests/

# Edge List Test Cases
FULLINS=$(TESTPATH)1-FullIns_3.col\
        $(TESTPATH)1-FullIns_4.col\
        $(TESTPATH)2-FullIns_3.col\
        $(TESTPATH)2-FullIns_4.col\
        $(TESTPATH)3-FullIns_3.col\
        $(TESTPATH)4-FullIns_3.col\
        $(TESTPATH)5-FullIns_3.col

INSERTIONS=$(TESTPATH)1-Insertions_4.col\
            $(TESTPATH)2-Insertions_3.col\
            $(TESTPATH)3-Insertions_3.col\
            $(TESTPATH)4-Insertions_3.col

ANNA=$(TESTPATH)anna.col

ASH=$(TESTPATH)ash331GPIA.col\
        $(TESTPATH)ash608GPIA.col\
        $(TESTPATH)ash958GPIA.col

DAVID=$(TESTPATH)david.col

DSJC=$(TESTPATH)DSJC125.1.col\
        $(TESTPATH)DSJC125.5.col\
        $(TESTPATH)DSJC125.9.col\
        $(TESTPATH)DSJC250.9.col

DSJR=$(TESTPATH)DSJR500.1c.col\
        $(TESTPATH)DSJR500.1.col\
        $(TESTPATH)DSJR500.5.col

FLAT=$(TESTPATH)flat300_28_0.col

FPSOL=$(TESTPATH)fpsol2.i.1.col\
        $(TESTPATH)fpsol2.i.2.col\
        $(TESTPATH)fpsol2.i.3.col

GAMES=$(TESTPATH)games120.col

HOMER=$(TESTPATH)homer.col

HUCK=$(TESTPATH)huck.col

INITHX=$(TESTPATH)inithx.i.1.col\
        $(TESTPATH)inithx.i.2.col\
        $(TESTPATH)inithx.i.3.col
            
JEAN=$(TESTPATH)jean.col

LE=$(TESTPATH)le450_15a.col\
    $(TESTPATH)le450_25a.col\
    $(TESTPATH)le450_25b.col\
    $(TESTPATH)le450_5c.col\
    $(TESTPATH)le450_5d.col
            
MILES=$(TESTPATH)miles250.col\
        $(TESTPATH)miles500.col\
        $(TESTPATH)miles750.col\
        $(TESTPATH)miles1000.col\
        $(TESTPATH)miles1500.col
            
MUG=$(TESTPATH)mug100_1.col\
        $(TESTPATH)mug100_25.col\
        $(TESTPATH)mug88_1.col\
        $(TESTPATH)mug88_25.col
            
MULSOL=$(TESTPATH)mulsol.i.1.col\
        $(TESTPATH)mulsol.i.2.col\
        $(TESTPATH)mulsol.i.3.col\
        $(TESTPATH)mulsol.i.4.col\
        $(TESTPATH)mulsol.i.5.col
        
MYCIEL=$(TESTPATH)myciel3.col\
        $(TESTPATH)myciel4.col\
        $(TESTPATH)myciel5.col\
        $(TESTPATH)myciel6.col
        
QUEEN=$(TESTPATH)queen5_5.col\
        $(TESTPATH)queen6_6.col\
        $(TESTPATH)queen7_7.col\
        $(TESTPATH)queen8_12.col\
        $(TESTPATH)queen8_8.col\
        $(TESTPATH)queen9_9.col\
        $(TESTPATH)queen10_10.col\
        $(TESTPATH)queen11_11.col\
        $(TESTPATH)queen12_12.col\
        $(TESTPATH)queen13_13.col\
        $(TESTPATH)queen14_14.col\
        $(TESTPATH)queen15_15.col
            
R125=$(TESTPATH)r125.1c.col\
        $(TESTPATH)r125.1.col\
        $(TESTPATH)r125.5.col
            
R250=$(TESTPATH)r250.1c.col\
        $(TESTPATH)r250.1.col\
        $(TESTPATH)r250.5.col

R1000=$(TESTPATH)r1000.1.col\
        $(TESTPATH)r1000.5.col

RTOTAL=$(R125)\
        $(R250)\
        $(R1000)
            
SCHOOL=$(TESTPATH)school1.col\
        $(TESTPATH)school1_nsh.col

WILL=$(TESTPATH)will199GPIA.col
            
ZEROIN=$(TESTPATH)zeroin.i.1.col\
        $(TESTPATH)zeroin.i.2.col\
        $(TESTPATH)zeroin.i.3.col

LIST=$(FULLINS)\
        $(INSERTIONS)\
        $(ANNA)\
        $(ASH)\
        $(DAVID)\
        $(DSJC)\
        $(DSJR)\
        $(FLAT)\
        $(FPSOL)\
        $(GAMES)\
        $(HOMER)\
        $(HUCK)\
        $(INITHX)\
        $(JEAN)\
        $(LE)\
        $(MILES)\
        $(MUG)\
        $(MULSOL)\
        $(MYCIEL)\
        $(QUEEN)\
        $(RTOTAL)\
        $(SCHOOL)\
        $(WILL)\
        $(ZERONI)

# Edge Matrix Test Cases
BONDYMURTY=$(TESTPATH)bondy_murty_7.txt\
            $(TESTPATH)bondy_murty_11.txt\
            $(TESTPATH)bondy_murty_14.txt\
            $(TESTPATH)bondy_murty_16.txt

CHVATAL=$(TESTPATH)chvatal_12.txt
        
CUBE=$(TESTPATH)cube_8.txt

DODECA=$(TESTPATH)dodecahedron_20.txt

GROTZSCH=$(TESTPATH)grotzsch_11.txt
            
GRUNBAUM=$(TESTPATH)grunbaum_25.txt

ICOSA=$(TESTPATH)icosahedron_12.txt
            
KURATOWSKI=$(TESTPATH)kuratowski_6.txt

INDIA=$(TESTPATH)map_of_india_30.txt
            
MYCIELSKI=$(TESTPATH)mycielski_5chromatic_23.txt\
            $(TESTPATH)mycielski_6chromatic_47.txt\
            $(TESTPATH)mycielski_7chromatic_95.txt
            
OCTA=$(TESTPATH)octahedron_6.txt
            
PETERSEN=$(TESTPATH)petersen_10.txt
            
RAMSEY=$(TESTPATH)ramsey_17.txt

TETRA=$(TESTPATH)tetrahedron_4.txt

WHEEL=$(TESTPATH)wheel_8.txt

MATRIX=$(BONDYMURTY)\
        $(CHVATAL)\
        $(CUBE)\
        $(DODECA)\
        $(GROTZSCH)\
        $(GRUNBAUM)\
        $(ICOSA)\
        $(KURATOWSKI)\
        $(INDIA)\
        $(MYCIELSKI)\
        $(OCTA)\
        $(PETERSEN)\
        $(RAMSEY)\
        $(TETRA)\
        $(WHEEL)
