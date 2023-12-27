
# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle ist ein automatischer statischer Analysator für NEAR-Smart-Contracts in Rust. Es kann helfen, Dutzende verschiedener Schwachstellen in NEAR-Smart-Contracts zu lokalisieren.
Laut [DefiLlama](https://defillama.com/chain/Near) wurden acht der Top-10-DApps in NEAR von BlockSec geprüft. Mit umfassender Prüfungserfahrung und einem tiefen Verständnis des NEAR-Protokolls haben wir dieses Tool entwickelt und teilen es mit der Community.

## Loslegen

### Voraussetzungen

#### Linux-Setup

Installieren Sie die erforderlichen Toolkits mit den folgenden Befehlen für **Rustle** unter Linux. Die Befehle wurden unter Ubuntu 20.04 LTS getestet.

```bash
# Rust-Toolchain installieren
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15 installieren
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# Python-Toolchain installieren
sudo apt install python3 python3-pip    # erfordert Python >= 3.8
pip3 install -r utils/requirements.txt  # Sie müssen dieses Repo zuerst klonen

# WASM-Ziel hinzufügen
rustup target add wasm32-unknown-unknown

# weitere Komponenten installieren
sudo apt install figlet
cargo install rustfilt

# [optional] nützliche Tools für die Entwicklung
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOS-Setup

Die folgenden Befehle sind für Benutzer, die macOS verwenden, und wurden nur auf Apple-Silicon-Macs getestet, daher sollten sie mit Vorsicht verwendet werden.

```bash
# Rust-Toolchain installieren
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15 installieren
brew install llvm@15

# Python-Pakete installieren
pip3 install -r utils/requirements.txt  # Sie müssen dieses Repo zuerst klonen
                                        # unter Verwendung der macOS-Standardversion von Python3

# WASM-Ziel hinzufügen
rustup target add wasm32-unknown-unknown

# weitere Komponenten installieren
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

Wir bieten eine Docker-Lösung an.

```bash
# Bild erstellen
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# Container aus dem Bild ausführen
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# Container ausführen
docker start rustle
docker exec -it -w /rustle rustle bash
```

### Verwendung

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`: Pfad zur Quelle des Vertrags.
* `tg_dir`: Pfad zum Build-Ziel des Vertrags. Standardmäßig identisch mit `src_dir`.
* `detector`: Die Detektorliste. Sie kann verwendet werden, um mehrere *Detektoren* oder *Gruppen* getrennt durch `,` zu übergeben. Standardmäßig auf `all` gesetzt.
  *   Übergeben Sie die `all`-Gruppe, um alle Detektoren zu aktivieren.
  *   Übergeben Sie die Gruppen `high`, `medium`, `low` und `info`, um Detektorgruppen mit unterschiedlichem Schweregrad zu aktivieren (siehe [Detektoren](#detectors)).
  *   Übergeben Sie die Gruppen `nep-ft`, `nep-storage` und `nep-nft`, um Detektoren zu aktivieren, die für bestimmte NEPs implementiert sind (siehe [NEP-Detektorgruppen](#nep-detector-groups)).
  *   Übergeben Sie Detektor-IDs aus der [Tabelle](#detectors), um diese Detektoren zu aktivieren.
* `output`: Pfad, in dem Prüfberichte generiert werden. Standardmäßig `./audit-result`.

Hinweis: Wenn der von Cargo erstellte Ziel-Bitcode (`.bc`-Datei) nicht im `src_dir` liegt, verwenden Sie `-t|--tg_dir`, um das Verzeichnis des Ziels festzulegen, sonst wird es standardmäßig auf `src_dir` gesetzt.

Der folgende Befehl zeigt ein Beispiel für die Analyse von LiNEAR.

```bash
# LiNEAR klonen
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# Rustle ausführen
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [optional] Rustle mit spezifizierten Detektoren oder Schweregradgruppen ausführen und Prüfberichte in `~/linear-report` speichern
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

Ein Bericht im CSV-Format wird im Verzeichnis `./audit-result` generiert.

## Detektoren

Alle Schwachstellen, die **Rustle** finden kann.

|Detektor-ID|Beschreibung|Schweregrad|
|---|---|---|
|`unhandled-promise`|[findet `Promises`, die nicht behandelt werden](docs/detectors/unhandled-promise.md)|Hoch|
|`non-private-callback`|[fehlendes Makro `#[private]` für Callback-Funktionen](docs/detectors/non-private-callback.md)|Hoch|
|`reentrancy`|[findet Funktionen, die anfällig für Reentrancy-Angriffe sind](docs/detectors/reentrancy.md)|Hoch|
|`unsafe-math`|[fehlende Überlaufprüfung bei arithmetischen Operationen](docs/detectors/unsafe-math.md)|Hoch|
|`self-transfer`|[fehlende Überprüfung von `sender != receiver`](docs/detectors/self-transfer.md)|Hoch|
|`incorrect-json-type`|[falscher Typ in Parametern oder Rückgabewerten verwendet](docs/detectors/incorrect-json-type.md)|Hoch|
|`unsaved-changes`|[Änderungen an Sammlungen werden nicht gespeichert](docs/detectors/unsaved-changes.md)|Hoch|
|`nft-approval-check`|[findet `nft_transfer` ohne Überprüfung der `approval id`](docs/detectors/nft-approval-check.md)|Hoch|
|`nft-owner-check`|[findet Genehmigungs- oder Widerrufsfunktionen ohne Eigentümerprüfung](docs/detectors/nft-owner-check.md)|Hoch|
|`div-before-mul`|[Präzisionsverlust aufgrund falscher Operationsreihenfolge](docs/detectors/div-before-mul.md)|Mittel|
|`round`|[Rundung ohne Angabe von `ceil` oder `floor`](docs/detectors/round.md)|Mittel|
|`lock-callback`|[Panik in der Callback-Funktion kann den Vertrag sperren](docs/detectors/lock-callback.md)|Mittel|
|`yocto-attach`|[kein `assert_one_yocto` in privilegierter Funktion](docs/detectors/yocto-attach.md)|Mittel|
|`dup-collection-id`|[doppelte ID-Verwendung in Sammlungen](docs/detectors/dup-collection-id.md)|Mittel|
|`unregistered-receiver`|[keine Panik bei nicht registrierten Übertragungsempfängern](docs/detectors/unregistered-receiver.md)|Mittel|
|`nep${id}-interface`|[findet alle nicht implementierten NEP-Schnittstellen](docs/detectors/nep-interface.md)|Mittel|
|`prepaid-gas`|[fehlende Überprüfung des vorausbezahlten Gases in `ft_transfer_call`](docs/detectors/prepaid-gas.md)|Niedrig|
|`non-callback-private`|[Makro `#[private]` in Nicht-Callback-Funktion verwendet](docs/detectors/non-callback-private.md)|Niedrig|
|`unused-ret`|[Funktionsergebnis wird nicht verwendet oder überprüft](docs/detectors/unused-ret.md)|Niedrig|
|`upgrade-func`|[keine Upgrade-Funktion im Vertrag](docs/detectors/upgrade-func.md)|Niedrig|
|`tautology`|[Tautologie in bedingtem Zweig verwendet](docs/detectors/tautology.md)|Niedrig|
|`storage-gas`|[fehlende Guthabenprüfung für Speichererweiterung](docs/detectors/storage-gas.md)|Niedrig|
|`unclaimed-storage-fee`|[fehlende Guthabenprüfung vor Speicherabmeldung](docs/detectors/unclaimed-storage-fee.md)|Niedrig|
|`inconsistency`|[Verwendung ähnlicher, aber leicht unterschiedlicher Symbole](docs/detectors/inconsistency.md)|Info|
|`timestamp`|[findet alle Verwendungen von `timestamp`](docs/detectors/timestamp.md)|Info|
|`complex-loop`|[findet alle Schleifen mit komplexer Logik, die zu DoS führen können](docs/detectors/complex-loop.md)|Info|
|`ext-call`|[findet alle vertragsübergreifenden Aufrufe](docs/detectors/ext-call.md)|Info|
|`promise-result`|[findet alle Verwendungen von Promise-Ergebnissen](docs/detectors/promise-result.md)|Info|
|`transfer`|[findet alle Transferaktionen](docs/detectors/transfer.md)|Info|
|`public-interface`|[findet alle öffentlichen Schnittstellen](docs/detectors/public-interface.md)|Info|

### NEP-Detektorgruppen

Neben den Gruppen nach Schweregrad bietet **Rustle** einige Detektorgruppen nach entsprechendem NEP an. Derzeit unterstützt **Rustle** die folgenden Gruppen.

|NEP|Detektorgruppen-ID|Detektor-IDs|
|---|---|---|
|[NEP-141][nep141]|`nep-ft`|`nep141-interface`, `self-transfer`, `unregistered-receiver`|
|[NEP-145][nep145]|`nep-storage`|`nep145-interface`, `unclaimed-storage-fee`|
|[NEP-171][nep171], [NEP-178][nep178]|`nep-nft`|`nep171-interface`, `nft-approval-check`, `nft-owner-check`|

## Neue Detektoren hinzufügen

1. Forken Sie dieses Repository auf Ihr Konto.
2. Legen Sie den neuen Detektor unter [/detectors](/detectors/) ab.
3. Fügen Sie ein Erkennungsziel in [/Makefile](/Makefile) mit Befehlen zum Ausführen Ihres Detektors hinzu.
4. Fügen Sie das Ziel zur Abhängigkeit des `audit`-Ziels und seinen Namen zur [Detektorliste](/rustle#L146) und [Schweregradgruppen](/rustle#L169) im `./rustle`-Skript hinzu.
5. Fügen Sie Verarbeitungscode in [utils/audit.py](/utils/audit.py) hinzu (siehe Code anderer Detektoren in `audit.py`).
6. Senden Sie einen Pull-Request von Ihrem Branch an den Hauptbranch.

## Hinweis

**Rustle** kann im Entwicklungsprozess verwendet werden, um NEAR-Smart-Contracts iterativ zu scannen. Dies kann viel manuellen Aufwand sparen und einen Teil potenzieller Probleme abmildern. Allerdings sind Schwachstellen in komplexer Logik oder im Zusammenhang mit Semantik immer noch eine Einschränkung von **Rustle**. Um komplizierte semantische Probleme zu lokalisieren, müssen die Experten von [BlockSec](https://blocksec.com/) umfassende und gründliche Überprüfungen durchführen. [Kontaktieren Sie uns](audit@blocksec.com) für einen Audit-Service.

## Lizenz

Dieses Projekt steht unter der AGPLv3-Lizenz. Den vollständigen Lizenztext finden Sie in der [LICENSE](LICENSE)-Datei.
