# ===============================================================================
# Dit is de ontvanger.
# Het is de taak van de ontvanger om de binnenkomende morsecode te vertalen naar letters.
# Deze worden dan op het scherm getoond.
#
# In een uitbreiding wordt het mogelijk om doorheen de ontvangen letters te scrollen.
# ===============================================================================

# ===============================================================================
# Opzetten van het programma: variabelen klaarmaken, radio instellen, ...
# ===============================================================================
basic.show_string("O")

# Opzetten van de radio
radio.off()
radio.on()
# TODO 1: vul hier het juiste nummer van jouw radiogroep in
radio.set_group(...)

# Test als de communicatie met de zender werkt
def on_received_number(receivedNumber):
    basic.show_number(receivedNumber)
radio.on_received_number(on_received_number)

ontvangen: List[str] = [] # Lijst die alle ontvangen letters bijhoudt
index = 0 # Index houdt bij waar in de lijst we zitten

# Lijst die morsecodes bevat.
# Elk element in de lijst is een koppel met dat er uit ziet als (morse, vertaling)
# TODO 2: Zorg ervoor dat het ook mogelijk wordt om andere tekens te ontcijferen.
#         Voorbeelden zijn: leestekens, cijfers, spatie, ...
#         Zoek op het internet wat de bijhorende morsecode is, of spreek dit af met je teamgenoot
morse_mapping = [
    [".-", "A"],
    ["-...", "B"],
    ["-.-.", "C"],
    ["-..", "D"],
    [".", "E"],
    ["..-.", "F"],
    ["--.", "G"],
    ["....", "H"],
    ["..", "I"],
    [".---", "J"],
    ["-.-", "K"],
    [".-..", "L"],
    ["--", "M"],
    ["-.", "N"],
    ["---", "O"],
    [".--.", "P"],
    ["--.-", "Q"],
    [".-.", "R"],
    ["...", "S"],
    ["-", "T"],
    ["..-", "U"],
    ["...-", "V"],
    [".--", "W"],
    ["-..-", "X"],
    ["-.--", "Y"],
    ["--..", "Z"]]

# ===============================================================================
# De code hieronder wordt 1 keer doorlopen wanneer er een bericht
# met tekst binnen komt.
#
# Ontvangt een morse bericht, vertaalt dit naar een gekend teken, slaat het op,
# en toont het op het scherm.
# ===============================================================================
def on_received_string(receivedString):
    global index # We passen index aan binnen deze functie --> global moet erbij
    message = receivedString

    # doorzoek alle morsecodes
    for paar in morse_mapping:
        
        # Kijk als het ontvangen bericht een bestaande morsecode is en wat de overeenkomende letter is
        # TODO 3: De code hieronder zou moeten controleren of de ontvangen morse bestaat, en wat de overeenkomende letter is.
        #         Pas de if-statement en de letter-toekenning aan zodat deze doen wat ze horen te doen.
        if False:
            letter = ""

            music.play(
                music.tone_playable(523, music.beat(BeatFraction.QUARTER)),
                music.PlaybackMode.IN_BACKGROUND
            )
            # voeg nieuwe letter toe aan lijst
            ontvangen.append(letter)

            # TODO 4: Verzet de index zodat deze achteraan de lijst van ontvangen letters komt.
            #         Zorg er dan voor dat de letter die je ontvangt op het scherm getoond wordt
            #         Gebruik hiervoor de nieuwe index.
            index = 0
            basic.show_string("FOUT")

    # TODO 5: Als het ontvangen bericht geen bestaande morsecode is, moet een vraagteken getoond worden.
    #         Hiervoor moet je zelf nog bijkomende logica implementeren.
    #
    #         Hint: je kan hiervoor een nieuwe variabele gebruiken die bijhoudt of je al een correcte code hebt gecheckt.

radio.on_received_string(on_received_string)

# ===============================================================================
# Uitbreiding: De code hieronder wordt 1 keer doorlopen op knop A wordt gedrukt.
# 
# Scrollt terug doorheen de ontvangen letters, en toont de letter op het scherm.
# ===============================================================================

# TODO: Wanneer we op knop a duwen, scrollen we terug doorheen de ontvangen letters
#       Verlaag hiervoor de index, en toon de letter op het scherm die bij deze index staat. 
#       Controleer eerst of je de index nog wel kan verlagen. We willen dat de index strict positief is.
def on_button_pressed_a():
    global index # We passen index aan binnen deze functie --> global moet erbij
    if False: 
        index = 0
        basic.show_string("FOUT")

input.on_button_pressed(Button.A, on_button_pressed_a)

# ===============================================================================
# Uitbreiding: De code hieronder wordt 1 keer doorlopen op knop B wordt gedrukt.
# 
# Scrollt vooruit doorheen de ontvangen letters, en toont de letter op het scherm.
# ===============================================================================

# TODO: Wanneer we op knop b duwen, scrollen we vooruit doorheen de ontvangen letters
#       Verhoog hiervoor de index, en toon de letter op het scherm die bij deze index staat. 
#       Controleer eerst of je de index nog wel kan verhogen. 
#       We willen niet dat de index buiten het bereik van de lijst gaat.
def on_button_pressed_b():
    pass # Vervang dit wanneer je de opdracht maakt
input.on_button_pressed(Button.B, on_button_pressed_b)
