#include "./lv_i18n.h"


////////////////////////////////////////////////////////////////////////////////
// Define plural operands
// http://unicode.org/reports/tr35/tr35-numbers.html#Operands

// Integer version, simplified

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static uint8_t en_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_lang = {
    .locale_name = "en",


    .locale_plural_fn = en_plural_fn
};

static lv_i18n_phrase_t de_singulars[] = {
    {"User name: %s", "Benutzer: %s"},
    {"Device Role: %s", "Gerätemodus: %s"},
    {"no new messages", "keine Nachrichten"},
    {"1 of 1 nodes online", "1/1 Gerät online"},
    {"User name: ", "Benutzer: "},
    {"Modem Preset: LONG FAST", "Modem: LONG FAST"},
    {"Channel: LongFast", "Gruppen-Kanäle: LongFast"},
    {"Role: Client", "Gerätemodus: Client"},
    {"Screen Timeout: 60s", "Bild aus: 60s"},
    {"Screen Brightness: 60%", "Bildschirmhelligkeit: 60%"},
    {"Screen Calibration: default", "Kalibrierung: Standard"},
    {"Input Control: none/none", "Eingabe: ohne/ohne"},
    {"Message Alert Buzzer: on", "Akustischer Alarm: ein"},
    {"Language: English", "Sprache: Deutsch"},
    {"Configuration Reset", "Einstellungen zurücksetzen"},
    {"Reboot / Shutdown", "Neustart / Ausschalten"},
    {"Group Channels", "Gruppen Kanäle"},
    {"no messages", "keine Nachrichten"},
    {"Settings", "Einstellungen"},
    {"Settings (advanced)", "Erweiterte Einstellungen"},
    {"Locations Map", "Karte"},
    {"no chats", "Keine Gespräche"},
    {"Node Options", "Optionen"},
    {"Short Name", "Kurzname"},
    {"Long Name", "Langname"},
    {"<unset>", "<leer>"},
    {"FrequencySlot: 1 (902.0MHz)", "Frequenz: 1 (902.0MHz)"},
    {"Brightness: 60%", "Helligkeit: 60%"},
    {"Timeout: 60s", "Bild aus: 60s"},
    {"Mouse", "Maus"},
    {"Keyboard", "Tastatur"},
    {"Message Alert", "Alarm"},
    {"NodeDB Reset\nFactory Reset", "Database Reset\nWerkseinstellungen"},
    {"Channel Name", "Kanalname"},
    {"Pre-shared Key", "Schlüssel"},
    {"New Message from\n", "Neue Nachricht von\n"},
    {"Resynch...", "Synchronisieren..."},
    {"Screen Calibration: %s", "Kalibrierung: %s"},
    {"done", "erledigt"},
    {"default", "Standard"},
    {"Modem Preset: %s", "Voreinstellung: %s"},
    {"Channel: %s", "Gruppen-Kanäle: %s"},
    {"Language: %s", "Sprache: %s"},
    {"Screen Lock: off", "Bildschirmsperre: aus"},
    {"Theme: Dark", "Farbschema: Dunkel"},
    {"Mesh Detector", "Mesh-Detektor"},
    {"Signal Scanner", "Signalstärke"},
    {"Trace Route", "Route verfolgen"},
    {"Neighbors", "Nachbarn"},
    {"Statistics", "Paketstatistik"},
    {"Packet Log", "Paket Historie"},
    {"Settings & Tools", "Einstellungen & Funktionen"},
    {"Node Search", "Gerätesuche"},
    {"Screen Lock", "Bildschirmsperre"},
    {"Lock PIN", "PIN"},
    {"Ringtone", "Klingelton"},
    {"Zone", "Gebiet"},
    {"City", "Stadt"},
    {"Unknown", "Unbekannt"},
    {"Offline", "Abwesend"},
    {"Public Key", "PKC Schlüssel"},
    {"Active Chat", "Aktiver Chat"},
    {"Telemetry", "Telemetrie"},
    {"Theme: %s", "Farbschema: %s"},
    {"Packet Statistics", "Paketstatistik"},
    {"none", "keine"},
    {"Default", "Standard"},
    {"Cancel", "Abbruch"},
    {"FrequencySlot: %d (%.2f MHz)", "Frequenz: %d (%.2f MHz)"},
    {"Brightness: %d%%", "Helligkeit: %d%%"},
    {"Timeout: off", "Timeout: aus"},
    {"Stop", "Stopp"},
    {"choose\nnode", "wähle\nNachbar"},
    {"choose target node", "wähle Ziel"},
    {"heard: !%08x", "Gehört: !%08x"},
    {"Packet Log: %d", "Paket Historie: %d"},
    {"Screen Timeout: off", "Display abschalten: nie"},
    {"Screen Timeout: %ds", "Display abschalten: %ds"},
    {"Screen Brightness: %d%%", "Helligkeit: %d%%"},
    {"Screen Lock: %s", "Bildschirmsperre: %s"},
    {"on", "ein"},
    {"off", "aus"},
    {"Message Alert: %s", "Klingelton: %s"},
    {"unknown", "unbekannt"},
    {"<no name>", "<kein Name>"},
    {"%d active chat(s)", "%d aktive Chat(s)"},
    {"New message from \n%s", "Neue Nachricht von \n%s"},
    {"Input Control: %s/%s", "Eingabegeräte: %s/%s"},
    {"%d of %d nodes online", "%d/%d Geräte online"},
    {"Filtering ...", "Filtern ..."},
    {"Filter: %d of %d nodes", "Filter: %d / %d Geräte"},
    {"now", "jetzt"},
    {"%d new message", "%d Nachricht"},
    {"%d new messages", "%d Nachrichten"},
    {"Tools", "Funktionen"},
    {"Highlight", "Hervorheben"},
    {"choose node", "wähle Nachbar"},
    {"Primary Channel", "Primärkanal"},
    {"Secondary Channels", "Sekundärkanal"},
    {"Dark\nLight", "Dunkel\nHell"},
    {NULL, NULL} // End mark
};



static uint8_t de_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t de_lang = {
    .locale_name = "de",
    .singulars = de_singulars,

    .locale_plural_fn = de_plural_fn
};

static lv_i18n_phrase_t es_singulars[] = {
    {"no new messages", "sin mensajes"},
    {"1 of 1 nodes online", "1 de 1 nodos online"},
    {"DEL", "BOR"},
    {"User name: ", "Nomb. Usua:"},
    {"Channel: LongFast", "Canal: LongFast"},
    {"Role: Client", "Rol: Cliente"},
    {"Screen Timeout: 60s", "Apag. Panta: 60s"},
    {"Screen Brightness: 60%", "Brillo Pantalla: 60%"},
    {"Screen Calibration: default", "Calibración Pantalla: predet."},
    {"Message Alert Buzzer: on", "Zumbador en mensaje: on"},
    {"Language: English", "Idioma: Español"},
    {"Configuration Reset", "Reiniciar Configuración"},
    {"Reboot / Shutdown", "Reiniciar / Apagar"},
    {"no messages", "sin mensajes"},
    {"Settings", "Configuración"},
    {"Settings (advanced)", "Configur. avanzada"},
    {"no chats", "sin chats"},
    {"Short Name", "Nom. Corto"},
    {"Long Name", "Nom. Largo"},
    {"Brightness: 60%", "Brillo: 60%"},
    {"Mouse", "Ratón"},
    {"Keyboard", "Teclado"},
    {"NodeDB Reset\\nFactory Reset", "Borrar NodeDB\\nReini. Fábrica"},
    {"Channel Name", "Nomb. Canal"},
    {"Pre-shared Key", "Clave Precomp."},
    {"New Message from\\n", "Nuevo msg de\\n"},
    {"User name: %s", "Nombre Usua: %s"},
    {"Device Role: %s", "Rol Dispo.: %s"},
    {"Screen Calibration: %s", "Calibración pant.: %s"},
    {"done", "hecho"},
    {"default", "defecto"},
    {"Region: %s", "Región: %s"},
    {"Channel: %s", "Canal: %s"},
    {"Language: %s", "Idioma: %s"},
    {"Screen Lock: off", "Bloq. Panta.: off"},
    {"Theme: Dark", "Tema: Oscuro"},
    {"Mesh Detector", "Detector Mesh"},
    {"Signal Scanner", "Escáner señal"},
    {"Trace Route", "Trazar ruta"},
    {"Neighbors", "Vecinos"},
    {"Statistics", "Estadísticas"},
    {"Packet Log", "Reg. Paquetes"},
    {"Settings & Tools", "Config y herramientas"},
    {"Node Search", "Buscar nodo"},
    {"Client\\nClient Mute\\n-- deprecated --\\nRouter\\nRepeater\\nTracker\\nSensor\\nTAK\\nClient Hidden\\nLost & Found\\nTAK Tracker", "Client\\nClient Mute\\n-- obsoleto --\\nRouter\\nRepeater\\nTracker\\nSensor\\nTAK\\nClient Hidden\\nLost & Found\\nTAK Tracker"},
    {"Light\\nDark", "Claro\\nOscuro"},
    {"Screen Lock", "Bloq. Panta."},
    {"Lock PIN", "PIN bloqu"},
    {"Ringtone", "Timbre"},
    {"Zone", "Zona"},
    {"City", "Ciudad"},
    {"Unknown", "Desconocido"},
    {"Public Key", "Clave Pública"},
    {"Hops away", "Saltos"},
    {"Position", "Posición"},
    {"Name", "Nombre"},
    {"Active Chat", "Chat Activo"},
    {"Telemetry", "Telemetría"},
    {"Theme: %s", "Tema: %s"},
    {"Packet Statistics", "Estadísticas"},
    {"LONG FAST\\nLONG SLOW\\n-- deprecated --\\nMEDIUM SLOW\\nMEDIUM FAST\\nSHORT SLOW\\nSHORT FAST\\nLONG MODERATE\\nSHORT TURBO", "LONG FAST\\nLONG SLOW\\n-- obsoleto --\\nMEDIUM SLOW\\nMEDIUM FAST\\nSHORT SLOW\\nSHORT FAST\\nLONG MODERATE\\nSHORT TURBO"},
    {"Client\\nClient Mute\\nRouter\\n-- deprecated --\\nRepeater\\nTracker\\nSensor\\nTAK\\nClient Hidden\\nLost & Found\\nTAK Tracker", "Client\\nClient Mute\\nRouter\\n-- obsoleto --\\nRepeater\\nTracker\\nSensor\\nTAK\\nClient Hidden\\nLost & Found\\nTAK Tracker"},
    {"Dark\\nLight", "Oscuro\\nClaro"},
    {"Brightness: %d%%", "Brillo : %d%%"},
    {"Stop", "Parar"},
    {"choose\\nnode", "escoge\\nnodo"},
    {"choose target node", "escoge nodo dest."},
    {"Packet Log: %d", "Reg. Paquetes: %d"},
    {"Screen Brightness: %d%%", "Brillo pantalla: %d%%"},
    {"Message Alert: %s", "Alerta Mensaje: %s"},
    {"unknown", "desconocido"},
    {"<no name>", "<sin nombre>"},
    {"%d active chat(s)", "%d chat(s) activos"},
    {"New message from \n%s", "Nuevo mensaje de\n%s"},
    {"%d of %d nodes online", "%d de %d nodos online"},
    {"Filtering ...", "Filtrando ..."},
    {"Filter: %d of %d nodes", "Filtro: %d de %d nodos"},
    {"now", "ahora"},
    {"%d new message", "%d nuev. mensaje"},
    {"%d new messages", "%d nuev. mensajes"},
    {NULL, NULL} // End mark
};



static uint8_t es_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);


    if ((n == 1)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t es_lang = {
    .locale_name = "es",
    .singulars = es_singulars,

    .locale_plural_fn = es_plural_fn
};

static uint8_t fi_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t fi_lang = {
    .locale_name = "fi",


    .locale_plural_fn = fi_plural_fn
};

static uint8_t fr_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);

    if ((((i == 0) || (i == 1)))) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t fr_lang = {
    .locale_name = "fr",


    .locale_plural_fn = fr_plural_fn
};

static uint8_t it_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t it_lang = {
    .locale_name = "it",


    .locale_plural_fn = it_plural_fn
};

static uint8_t pl_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);
    uint32_t i10 = i % 10;
    uint32_t i100 = i % 100;
    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    if ((v == 0 && (2 <= i10 && i10 <= 4) && (!(12 <= i100 && i100 <= 14)))) return LV_I18N_PLURAL_TYPE_FEW;
    if ((v == 0 && i != 1 && (0 <= i10 && i10 <= 1)) || (v == 0 && (5 <= i10 && i10 <= 9)) || (v == 0 && (12 <= i100 && i100 <= 14))) return LV_I18N_PLURAL_TYPE_MANY;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t pl_lang = {
    .locale_name = "pl",


    .locale_plural_fn = pl_plural_fn
};

static uint8_t pt_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);

    if (((0 <= i && i <= 1))) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t pt_lang = {
    .locale_name = "pt",


    .locale_plural_fn = pt_plural_fn
};

static uint8_t ro_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);
    uint32_t n100 = n % 100;
    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    if ((v != 0) || (n == 0) || (n != 1 && (1 <= n100 && n100 <= 19))) return LV_I18N_PLURAL_TYPE_FEW;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t ro_lang = {
    .locale_name = "ro",


    .locale_plural_fn = ro_plural_fn
};

static lv_i18n_phrase_t se_singulars[] = {
    {"no new messages", "inga nya meddelanden"},
    {"1 of 1 nodes online", "1 av 1 noder online"},
    {"uptime 00:00:00", "upptid 00:00:00"},
    {"User name: ", "Användarnamn: "},
    {"Modem Preset: LONG FAST", "Förinställning: Lång räckvidd / Snabb"},
    {"Channel: LongFast", "Kanal: LongFast"},
    {"Role: Client", "Roll: Klient"},
    {"Screen Timeout: 60s", "Bildskärms Timeout: 60s"},
    {"Screen Lock: off", "Bildskärms Lås: av"},
    {"Screen Brightness: 60%", "Bildskärmens Ljusstyrka: 60%"},
    {"Theme: Dark", "Tema: Mörkt"},
    {"Screen Calibration: default", "Bildskärmens Kalibrering: standard"},
    {"Input Control: none/none", "Inmatningsmetod: ingen/ingen"},
    {"Message Alert Buzzer: on", "Meddelande varningsklocka: på"},
    {"Language: English", "Språk: Engelska"},
    {"Configuration Reset", "Återställ konfiguration"},
    {"Reboot / Shutdown", "Starta om / Stäng av"},
    {"Mesh Detector", "Meshdetektor"},
    {"Signal Scanner", "Signalskanner"},
    {"Trace Route", "Traceroute (spåra rutt)"},
    {"Neighbors", "Grannar"},
    {"Statistics", "Statistik"},
    {"Packet Log", "Paket Loggbok"},
    {"Group Channels", "Kanaler"},
    {"no messages", "inga meddelanden"},
    {"Settings & Tools", "Inställningar & Verktyg"},
    {"Settings (advanced)", "Inställningar (Avancerat)"},
    {"Locations Map", "Karta"},
    {"no chats", "inga chattar"},
    {"Node Search", "Sök nod"},
    {"Packet Statistics", "Paket Statistik"},
    {"Node Options", "Nod alternativ"},
    {"Short Name", "Kort Namn"},
    {"Long Name", "Lånt Namn"},
    {"<unset>", "<ej inställt>"},
    {"LONG FAST\nLONG SLOW\n-- deprecated --\nMEDIUM SLOW\nMEDIUM FAST\nSHORT SLOW\nSHORT FAST\nLONG MODERATE\nSHORT TURBO", "Lång räckvidd / Snabb\nLång räckvidd / Långsam\n-- utfasad --\nMedium Räckvidd / Långsam\nMedium räckvidd / Snabb\nKort räckvidd / Långsam\nKort räckvidd / Snabb\nLång räckvidd / Måttlig\nKort räckvidd / Turbo"},
    {"Client\nClient Mute\nRouter\n-- deprecated --\nRepeater\nTracker\nSensor\nTAK\nClient Hidden\nLost & Found\nTAK Tracker", "Klient\nKlient Stum\nRouter\n-- utfasad --\nRelästation\nSpårare\nSensor\nTAK\nKlient Gömd\nFörlorad & hittad\nTAK Spårare"},
    {"Brightness: 60%", "Ljusstyrka: 60%"},
    {"Dark\nLight", "Mörkt\nLjust"},
    {"Screen Lock", "Bildskärms Lås"},
    {"Lock PIN", "Lås PIN"},
    {"Mouse", "Mus"},
    {"none", "ingen"},
    {"Keyboard", "Tangentbord"},
    {"Message Alert", "Meddelande Varning"},
    {"Ringtone", "Ringsignal"},
    {"Default", "Standard"},
    {"Zone", "Zon"},
    {"City", "Stad"},
    {"NodeDB Reset\nFactory Reset", "Nollställ NodeDB\nFabriksåterställning"},
    {"Channel Name", "Kanal Namn"},
    {"Pre-shared Key", "Tidigare delad Nyckel"},
    {"Unknown", "Okänd"},
    {"Offline", "Frånkopplad"},
    {"Public Key", "Publik Nyckel"},
    {"Hops away", "Hopp bort"},
    {"Position", "Position"},
    {"Name", "Namn"},
    {"Active Chat", "Aktiv Chatt"},
    {"Telemetry", "Telemetri"},
    {"Start", "Kör"},
    {"New Message from\n", "Nytt meddelande från\n"},
    {"Resynch...", "Synkronisera om..."},
    {"Cancel", "Avbryt"},
    {"FrequencySlot: %d (%.2f MHz)", "Frekvensplats: %d (%.2f MHz)"},
    {"Brightness: %d%%", "Ljusstyrka: %d%%"},
    {"Timeout: off", "Timeout: av"},
    {"Screen Calibration: %s", "Bildskärmens Kalibrering: %s"},
    {"done", "klar"},
    {"default", "standard"},
    {"Stop", "Stopp"},
    {"choose\nnode", "välj\nnod"},
    {"choose target node", "välj mål nod"},
    {"heard: !%08x", "hört: !%08x"},
    {"Packet Log: %d", "Paket Loggbok: %d"},
    {"Language: %s", "Språk: %s"},
    {"Screen Timeout: off", "Bildskärms Timeout: av"},
    {"Screen Timeout: %ds", "Bildskärms Timeout: %ds"},
    {"Screen Brightness: %d%%", "Bildskärmens Ljusstyrka: %d%%"},
    {"Theme: %s", "Tema: %s"},
    {"User name: %s", "Användarnamn: %s"},
    {"Device Role: %s", "Roll: %s"},
    {"Region: %s", "Region: %s"},
    {"Modem Preset: %s", "Förinställning: %s"},
    {"Channel: %s", "Kanal: %s"},
    {"Screen Lock: %s", "Bildskärms Lås: %s"},
    {"on", "på"},
    {"off", "av"},
    {"Message Alert: %s", "Meddelande Varning: %s"},
    {"hops: %d", "hopp: %d"},
    {"unknown", "okänd"},
    {"<no name>", "<inget namn>"},
    {"%d active chat(s)", "%d aktiva chatt(ar)"},
    {"New message from \n%s", "Nytt meddelande från \n%s"},
    {"Input Control: %s/%s", "Inmatningsmetod: %s/%s"},
    {"%d of %d nodes online", "%d av %d noder online"},
    {"Filtering ...", "Filtrerar ..."},
    {"Filter: %d of %d nodes", "Filter: %d av %d noder"},
    {"now", "nu"},
    {"%d new message", "%d nytt meddelande"},
    {"%d new messages", "%d nya meddelanden"},
    {"uptime: %02d:%02d:%02d", "upptid: %02d:%02d:%02d"},
    {"Tools", "Verktyg"},
    {"Highlight", "Markera"},
    {"Settings", "Inställningar"},
    {NULL, NULL} // End mark
};



static uint8_t se_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);


    if ((n == 1)) return LV_I18N_PLURAL_TYPE_ONE;
    if ((n == 2)) return LV_I18N_PLURAL_TYPE_TWO;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t se_lang = {
    .locale_name = "se",
    .singulars = se_singulars,

    .locale_plural_fn = se_plural_fn
};

static uint8_t tr_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);


    if ((n == 1)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t tr_lang = {
    .locale_name = "tr",


    .locale_plural_fn = tr_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &en_lang,
    &de_lang,
    &es_lang,
    &fi_lang,
    &fr_lang,
    &it_lang,
    &pl_lang,
    &pt_lang,
    &ro_lang,
    &se_lang,
    &tr_lang,
    NULL // End mark
};

////////////////////////////////////////////////////////////////////////////////


// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
 * Reset internal state. For testing.
 */
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
 * Set the languages for internationalization
 * @param langs pointer to the array of languages. (Last element has to be `NULL`)
 */
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
    if(langs == NULL) return -1;
    if(langs[0] == NULL) return -1;

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
 * Change the localization (language)
 * @param l_name name of the translation locale to use. E.g. "en-GB"
 */
int lv_i18n_set_locale(const char * l_name)
{
    if(current_lang_pack == NULL) return -1;

    uint16_t i;

    for(i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
    uint16_t i;
    for(i = 0; trans[i].msg_id != NULL; i++) {
        if(strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if(trans[i].translation) return trans[i].translation;
        }
    }

    return NULL;
}


/**
 * Get the translation from a message ID
 * @param msg_id message ID
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text(const char * msg_id)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;

    // Search in current locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    return msg_id;
}

/**
 * Get the translation from a message ID and apply the language's plural rule to get correct form
 * @param msg_id message ID
 * @param num an integer to select the correct plural form
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    return msg_id;
}

/**
 * Get the name of the currently used locale.
 * @return name of the currently used locale. E.g. "en-GB"
 */
const char * lv_i18n_get_current_locale(void)
{
    if(!current_lang) return NULL;
    return current_lang->locale_name;
}
