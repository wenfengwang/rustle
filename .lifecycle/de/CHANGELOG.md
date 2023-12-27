
<a name="v2.0"></a>
# [v2.0](https://github.com/blocksecteam/rustle/releases/tag/v2.0) – 07. April 2023

## Was hat sich geändert?

* Unterstützung für macOS hinzugefügt, siehe [README](/README.md#macos-setup) für weitere Informationen

**Vollständiges Änderungsprotokoll**: https://github.com/blocksecteam/rustle/compare/v1.3...v2.0

[Änderungen][v2.0]

<a name="v1.3"></a>
# [v1.3](https://github.com/blocksecteam/rustle/releases/tag/v1.3) – 13. Januar 2023

## Was hat sich geändert?

* 3 neue Detektoren hinzugefügt
  *   [unclaimed-storage-fee](/docs/detectors/unclaimed-storage-fee.md): Funktionen ohne Guthabenprüfung vor der Speicherabmeldung finden (basierend auf [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md))
  *   [nft-approval-check](/docs/detectors/nft-approval-check.md): `nft_transfer` ohne Überprüfung der `approval id` finden (basierend auf [NEP-171](https://github.com/near/NEPs/blob/master/neps/nep-0171.md))
  *   [nft-owner-check](/docs/detectors/nft-owner-check.md): Funktionen zum Genehmigen oder Widerrufen ohne Eigentümerprüfung finden (basierend auf [NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md))
* Neue Detektorgruppen `nep-ft`, `nep-storage` und `nep-nft` hinzugefügt

**Vollständiges Änderungsprotokoll**: https://github.com/blocksecteam/rustle/compare/v1.2...v1.3

[Änderungen][v1.3]

<a name="v1.2"></a>
# [v1.2](https://github.com/blocksecteam/rustle/releases/tag/v1.2) – 16. Dezember 2022

## Was hat sich geändert?

* 6 neue Detektoren hinzugefügt
  *   [public-interface](/docs/detectors/public-interface.md): Alle öffentlichen Schnittstellen finden
  *   [dup-collection-id](/docs/detectors/dup-collection-id.md): Doppelte ID-Verwendungen in Sammlungen finden
  *   [storage-gas](/docs/detectors/storage-gas.md): Fehlende Guthabenprüfungen für Speichererweiterungen finden
  *   [unregistered-receiver](/docs/detectors/unregistered-receiver.md): Übertragungsfunktionen ohne Panik bei nicht registrierten Empfängern finden
  *   [unsaved-changes](/docs/detectors/unsaved-changes.md): Änderungen an Sammlungen, die nicht gespeichert sind, finden
  *   [nep${id}-interface](/docs/detectors/nep-interface.md): Schnittstellenintegrität für verschiedene NEP-Spezifikationen überprüfen
* Unterstützung für rustc v1.65.0 hinzugefügt
* clang-tidy zur Codeoptimierung integriert

**Vollständiges Änderungsprotokoll**: https://github.com/blocksecteam/rustle/compare/v1.1...v1.2

[Änderungen][v1.2]

<a name="v1.1"></a>
# [v1.1](https://github.com/blocksecteam/rustle/releases/tag/v1.1) – 10. November 2022

## Änderungen

* Dokumentation: [Beispiele](/examples) für jeden Detektor hinzugefügt
* Feature: LLVM-Version auf 15 erhöht (wir arbeiten jedoch noch an der Unterstützung von Rust v1.65.0, siehe diese [PR](https://github.com/rust-lang/rust/pull/99464/) für weitere Informationen)
* Feature: Unit-Test-Skripte hinzugefügt
* Feature: `--output`-Flag zum [Rustle](/rustle)-Skript hinzugefügt
* Feature: Schwachstellen im Prüfbericht in verschiedene Schweregradgruppen eingeteilt
* Mehrere Fehler behoben

**Vollständiges Änderungsprotokoll**: https://github.com/blocksecteam/rustle/compare/v1.0...v1.1

[Änderungen][v1.1]

<a name="v1.0"></a>
# [v1.0](https://github.com/blocksecteam/rustle/releases/tag/v1.0) – 01. November 2022

Wir freuen uns, [Rustle](https://github.com/blocksecteam/rustle) vorzustellen: den ersten automatischen Auditor, den [BlockSec](https://blocksec.com/) für die NEAR-Community anbietet.

Rustle hat mehrere herausragende Funktionen:

* Rustle kann derzeit über 20 verschiedene Problemtypen in NEAR-Verträgen erkennen. Siehe den Abschnitt Detektoren für die vollständige Liste.
* Rustle ist einfach zu verwenden. Wir bieten detaillierte Installationsanweisungen und Tutorials. Zusätzlich stellen wir auch ein Docker-Image für einen schnellen Einstieg zur Verfügung.
* Rustle ist sehr schnell, die meisten NEAR-Verträge können innerhalb von 3 Minuten analysiert werden.
* Rustle ist benutzerfreundlich mit Berichten im CSV- und JSON-Format. Wir bieten zudem ein Skript an, um Ihnen beim Importieren der Ergebnisse in [Notion](https://www.notion.so/) zu helfen.

[Änderungen][v1.0]


<!-- Generated by https://github.com/rhysd/changelog-from-release v3.7.0 -->
