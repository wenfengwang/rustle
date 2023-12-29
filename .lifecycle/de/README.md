
# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle ist ein automatischer statischer Analysator für NEAR-Smart-Contracts in Rust. Es kann dabei helfen, Dutzende verschiedener Schwachstellen in NEAR-Smart-Contracts zu lokalisieren.
Laut [DefiLlama](https://defillama.com/chain/Near) wurden acht der Top-10-DApps in NEAR von BlockSec geprüft. Mit umfassender Prüfungserfahrung und einem tiefen Verständnis des NEAR-Protokolls haben wir dieses Tool entwickelt und teilen es mit der Community.

## Loslegen

### Voraussetzungen

#### Linux-Setup

Installieren Sie die erforderlichen Toolkits mit den folgenden Befehlen für **Rustle** unter Linux. Die Befehle wurden unter Ubuntu 20.04 LTS getestet.

```bash
# install Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# install LLVM 15
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# install Python toolchain
sudo apt install python3 python3-pip    # requires python >= 3.8
pip3 install -r utils/requirements.txt  # you need to clone this repo first

# add WASM target
rustup target add wasm32-unknown-unknown

# install other components
sudo apt install figlet
cargo install rustfilt

# [optional] useful tools for developing
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOS-Setup

Die folgenden Befehle richten sich an Benutzer, die macOS verwenden. Sie wurden nur auf Apple Silicon Macs getestet, daher ist Vorsicht geboten.

```bash
# install Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# install LLVM 15
brew install llvm@15

# install Python packages
pip3 install -r utils/requirements.txt  # you need to clone this repo first
                                        # using macOS default python3

# add WASM target
rustup target add wasm32-unknown-unknown

# install other components
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

Wir bieten eine Docker-Lösung an.

```bash
# build the image
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# run a container from the image
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# exec the container
docker start rustle
docker exec -it -w /rustle rustle bash
```

### Verwendung

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`: Pfad zur Vertragsquelle.
* `tg_dir`: Pfad zum Vertrags-Build-Ziel. Standardmäßig identisch mit `src_dir`.
* `detector`: Die Detektorliste. Sie kann verwendet werden, um mehrere *Detektoren* oder *Gruppen* getrennt durch `,` zu übergeben. Standardmäßig `all`.
  *   Übergeben Sie `all` als *Gruppe*, um alle Detektoren zu aktivieren.
  *   Übergeben Sie `high`, `medium`, `low` und `info` als *Gruppen*, um Detektorgruppen mit unterschiedlichem Schweregrad zu aktivieren (siehe [Detektoren](#detectors)).
  *   Übergeben Sie `nep-ft`, `nep-storage` und `nep-nft` als *Gruppen*, um Detektoren zu aktivieren, die für bestimmte NEPs implementiert sind (siehe [NEP-Detektorgruppen](#nep-detector-groups)).
  *   Übergeben Sie *Detektor-IDs* aus der [Tabelle](#detectors), um diese Detektoren zu aktivieren.
* `output`: Pfad, in dem Prüfberichte generiert werden. Standardmäßig `./audit-result`.

Hinweis: Wenn der von Cargo erstellte Zielbitcode (`.bc`-Datei) nicht im `src_dir` liegt, verwenden Sie `-t|--tg_dir`, um das Verzeichnis des Ziels festzulegen, sonst wird es standardmäßig auf `src_dir` gesetzt.

Der folgende Befehl zeigt ein Beispiel für die Analyse von LiNEAR.

```bash
# clone LiNEAR
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# run Rustle
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [optional] run Rustle on specified detectors or severity groups and save audit reports in `~/linear-report`
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

Ein Bericht im CSV-Format wird im Verzeichnis `./audit-result` generiert.

## Detektoren

Alle Schwachstellen, die **Rustle** finden kann.

|Detektor-ID|Beschreibung|Schweregrad|
|---|---|---|
|`unhandled-promise`|[findet `Promises`, die nicht behandelt werden](docs/detectors/unhandled-promise.md)|Hoch|
|`non-private-callback`|[fehlendes Makro `#[private]` für Callback-Funktionen](docs/detectors/non-private-callback.md)|Hoch|
|`reentrancy`|[findet Funktionen, die anfällig für Wiedereintrittsangriffe sind](docs/detectors/reentrancy.md)|Hoch|
|`unsafe-math`|[fehlende Überlaufprüfung für arithmetische Operationen](docs/detectors/unsafe-math.md)|Hoch|
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
|`non-callback-private`|[Makro `#[private]` wird in Nicht-Callback-Funktion verwendet](docs/detectors/non-callback-private.md)|Niedrig|
|`unused-ret`|[Funktionsergebnis wird nicht verwendet oder überprüft](docs/detectors/unused-ret.md)|Niedrig|
|`upgrade-func`|[keine Upgrade-Funktion im Vertrag](docs/detectors/upgrade-func.md)|Niedrig|
|`tautology`|[Tautologie wird im bedingten Zweig verwendet](docs/detectors/tautology.md)|Niedrig|
|`storage-gas`|[fehlende Bilanzprüfung für Speichererweiterung](docs/detectors/storage-gas.md)|Niedrig|
|`unclaimed-storage-fee`|[fehlende Guthabenprüfung vor der Speicherabmeldung](docs/detectors/unclaimed-storage-fee.md)|Niedrig|
|`inconsistency`|[Verwendung eines ähnlichen, aber leicht unterschiedlichen Symbols](docs/detectors/inconsistency.md)|Info|
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
6. Senden Sie eine Pull-Anfrage von Ihrem Branch an den Hauptbranch.

## Hinweis

**Rustle** kann im Entwicklungsprozess verwendet werden, um NEAR-Smart-Contracts iterativ zu scannen. Dies kann viel manuellen Aufwand einsparen und einen Teil potenzieller Probleme mindern. Allerdings sind Schwachstellen in komplexer Logik oder im Zusammenhang mit Semantik immer noch die Einschränkung von **Rustle**. Um komplizierte semantische Probleme zu lokalisieren, müssen die Experten von [BlockSec](https://blocksec.com/) umfassende und gründliche Überprüfungen durchführen. [Kontaktieren Sie uns](audit@blocksec.com) für einen Audit-Service.

## Lizenz

Dieses Projekt steht unter der AGPLv3-Lizenz. Den vollständigen Lizenztext finden Sie in der [LICENSE](LICENSE)-Datei.
