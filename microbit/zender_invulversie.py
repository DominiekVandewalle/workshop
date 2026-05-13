# ===============================================================================
# Dit is de zender. 
# De taak van de zender is om morsetekens (punten en strepen) op te nemen.
# Vervolgens worden die over de radio doorgestuurd naar de ontvanger.
#
# In een uitbreiding wordt een mogelijkheid toegevoegd om het huidige bericht te resetten.
# ===============================================================================

# ===============================================================================
# Opzetten van het programma: variabelen klaarmaken, radio instellen, ...
# ===============================================================================
basic.show_string("Z")

# Opzetten van de radio
radio.off()
radio.on()
# TODO 1: vul hier het juiste nummer van jouw radiogroep in
radio.set_group(...)
radio.send_number(0) # test als de ontvanger dit cijfer ontvangt

# Hoe lang (in ms) je op de knop moet duwen voor het gezien wordt als "-"
# TODO 2: verander de threshold naar een realistische en praktische waarde.
THRESHOLD = 1

# Bijhouden van ingedrukte tekens
huidig = ""

# ===============================================================================
# Dit is de hoofdlus, wat hierbinnen staat wordt constant herhaald uitgevoerd
# Wanneer je aan dit deel code begint, moet je de aanhalingstekens weghalen
# Deze staan zowel voor de lus, als erna en moeten allemaal verwijderd worden
# ===============================================================================
'''
def on_forever():
    # Zorgt ervoor dat deze functie de variabele "huidig" kan aanpassen
    global huidig

    # knop A ingedrukt?
    if input.button_is_pressed(Button.A):
        duration = 0

        # meet hoe lang knop A wordt ingedrukt
        while input.button_is_pressed(Button.A):
            # TODO 4: Bekijk onderstaande code. Wat is er mis mee? Probeer het eens uit
            #         Pas dit aan zodat het programma beter werkt en responsiever is.
            basic.pause(500)
            duration += 500

        # korte druk = punt
        # TODO 5: Vul de if-statement aan. Denk hiervoor na wat we vergelijken.
        #         Test dit ook met de ontvanger vanaf je kan!
        if False:
            huidig = "" + huidig + "."
            music.play(music.tone_playable(262, music.beat(BeatFraction.EIGHTH)),
                music.PlaybackMode.IN_BACKGROUND)
            basic.show_string(".")

        # lange druk = streep
        else:
            pass # TODO 6: verwijder "pass". Dit staat er zodat de code toch werkt zolang je TODO 6 niet maakt.
            # TODO 6: Hieronder ontbreekt nog code. Vul de code aan zodat:
            #         - Een streepje (-) wordt toegevoegd aan het huidige bericht
            #         - Een langere toon wordt afgespeeld dan bij het punt 
            #         - Een streepje wordt getoond op het scherm
            #         Test deze code opnieuw vanaf je kan!

        basic.clear_screen()

    # knop B verstuurt de volledige morsecode
    # TODO 3: Zorg ervoor dat we het huidige morseteken verzenden als knop B wordt ingedrukt
    #         Pas hiervoor de if-statement aan, en de lijn eronder die een string verzendt via de radio.
    if False: # 
        radio.send_string("FOUT")
        basic.show_string("S", 60)
        basic.show_string("e", 60)
        basic.show_string("n", 60)
        basic.show_string("t", 60)
        huidig = ""
        basic.clear_screen()

# Voer de code constant uit
basic.forever(on_forever)
'''

# ===============================================================================
# Uitbreiding: wanneer het logo wordt ingedrukt, reset je het huidige morseteken
#              Als je hieraan begint, moet je de aanhalingstekens weghalen
# ===============================================================================
'''
def on_logo_pressed():
    # TODO: maak het huidige bericht leeg en toon een icoontje (bv. NO of SAD)
input.on_logo_event(TouchButtonEvent.PRESSED, on_logo_pressed)
'''