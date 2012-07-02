/**
 ******************************************************************************
 * @file pt100lib.c
 * @brief Bibiliothek mit PT100 Funktionen
 * @author Roman Buchert (roman.buchert@googlemail.com)
 ******************************************************************************/
/******************************************************************************/

/*
 ******************************************************************************
 * INCLUDE-Dateien
 ******************************************************************************/
#include <pt100lib.h>
#include <pt100_table.h>
/******************************************************************************/

/**
 ******************************************************************************
 * @brief Wandelt einen PT100-Widerstandswert in eine Temperatur um
 * @param u32Widerstand  Widerstand in mOhm
 * @return Temperatur in °mC
 ******************************************************************************/
__s32 pt100_R2T(__u32 u32Widerstand)
{
  __u16 u16WidCntr;
  __s32 s32T, s32T1;    //Hilfsvariablen Temperatur
  __u32 u32R1, u32R2;   //Hilfsvariablen Widerstand

  // Prüfe, ob Widerstand innerhalb der Tabelle liegt
  if (u32Widerstand > R_MAX)
  {
    u32Widerstand = R_MAX;
  }
  else if (u32Widerstand < R_MIN)
  {
    u32Widerstand = R_MIN;
  }

  // Suche nächst größeren Widerstand aus der Tabelle
  for(u16WidCntr = 0; u32Widerstand > pt100_table[u16WidCntr]; u16WidCntr++);

  // Bereichsprüfung unten
  if (!u16WidCntr)
  {
    u32Widerstand = R_MIN;
    u16WidCntr++;
  }

  // Bereichsprüfung oben
  if (u16WidCntr > R_MAX)
  {
    u32Widerstand = R_MAX;
    u16WidCntr = INDEX_MAX + 1;
  }

  // nächst kleineren Widerstand auswählen
  u16WidCntr--;

  /**
   *  Temperatur berechnen
   * \f[ T = T1 + \frac{(T2-T1)*(R-R1)}{(R2-R1)} \f]
   *          (T2 -T1) x (R - R1)       \n
   * T = T1 + -------------------       \n
   *               (R2 - R1)            \n
   *
   * T  : berechnete Temperatur                                 \n
   * T1 : Temperaturtabellenwert unter gemessenem Widerstand    \n
   * T2 : Temperaturtabellenwert über gemessenem Widerstand     \n
   *
   * R  : gemessener Widerstand                                 \n
   * R1 : Widerstandstabellenwert unter gemessenem Widerstand   \n
   * R2 : Widerstandstabellenwert über gemessenem Widerstand    \n
   *
   * (Quelle: Elektrische Temperaturmessung (M. Nau / jumo))
   */

  s32T1 = ((__s32) u16WidCntr - (__s32)INDEX_ZERO) * (__s32) T_DIFF;
  u32R1 = pt100_table[u16WidCntr];
  u32R2 = pt100_table[u16WidCntr + 1];

  s32T = (s32T1 + ((T_DIFF * (u32Widerstand - u32R1)) / (u32R2 - u32R1)));

  return (s32T);

}
/******************************************************************************/

/**
 ******************************************************************************
 * @brief Wandelt eine Temperatur in einen Pt100 Widerstandswert
 * @param s32Temperatur Temperatur in m°C
 * @return Widerstand in mOhm
 ******************************************************************************/
__u32 pt100_T2R( __s32 s32Temperatur)
{
  __u16 u16TmpCntr;
  __s32 s32T, s32T1;            //Hilfsvariablen Temperatur
  __u32 u32R, u32R1, u32R2;     //Hilfsvariablen Widerstand

  // Prüfe, ob Temperatur innerhalb der Tabelle liegt
  if (s32Temperatur < T_MIN)
  {
    s32Temperatur = T_MIN;
  }
  else if (s32Temperatur > T_MAX)
  {
    s32Temperatur = T_MAX;
  }

  // Suche Widerstandswerte
  s32T = s32Temperatur + labs(T_MIN);
  u16TmpCntr = (__u16)(s32T / (__s32)T_DIFF);

  //Array begrenzen
  if (u16TmpCntr == INDEX_MAX)
  {
    u16TmpCntr = INDEX_MAX - 1;
  }
  /**
   *  Widerstand berechnen
   * \f[ R = R1 + \frac{(R2-R1)*(T-T1)}{(T2-T1)} \f]
   *          (R2 -R1) x (T - T1)       \n
   * R = R1 + -------------------       \n
   *               (T2 - T1)            \n
   *
   * T  : berechnete Temperatur                                 \n
   * T1 : Temperaturtabellenwert unter gemessenem Widerstand    \n
   * T2 : Temperaturtabellenwert über gemessenem Widerstand     \n
   *
   * R  : gemessener Widerstand                                 \n
   * R1 : Widerstandstabellenwert unter gemessenem Widerstand   \n
   * R2 : Widerstandstabellenwert über gemessenem Widerstand    \n
   *
   * (Quelle: Elektrische Temperaturmessung (M. Nau / jumo))
   */

  s32T1 = (s32T / (__s32)T_DIFF) * T_DIFF;
  u32R1 = pt100_table[u16TmpCntr];
  u32R2 = pt100_table[u16TmpCntr + 1];

  u32R = u32R1 + (((s32T - s32T1)*(u32R2-u32R1))/(T_DIFF));

  return (u32R);
}
/******************************************************************************/

/**
 ******************************************************************************
 * @brief
 * @param
 * @return
 ******************************************************************************/
/******************************************************************************/

/**
 ******************************************************************************
 * @brief
 * @param
 * @return
 ******************************************************************************/
/******************************************************************************/

/**
 ******************************************************************************
 * @brief
 * @param
 * @return
 ******************************************************************************/
/******************************************************************************/

