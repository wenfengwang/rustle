
# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle est un analyseur statique automatique pour les contrats intelligents NEAR écrits en Rust. Il peut aider à identifier des dizaines de vulnérabilités différentes dans les contrats intelligents NEAR.
Selon [DefiLlama](https://defillama.com/chain/Near), parmi les 10 principales DApps sur NEAR, 8 ont été auditées par BlockSec. Forts d'une riche expérience d'audit et d'une compréhension approfondie du protocole NEAR, nous avons développé cet outil et le partageons avec la communauté.

## Pour commencer

### Prérequis

#### Configuration pour Linux

Installez les outils nécessaires avec les commandes suivantes pour **Rustle** sous Linux. Les commandes ont été testées sous Ubuntu 20.04 LTS.

```bash
# installer Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# installer LLVM 15
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# installer Python toolchain
sudo apt install python3 python3-pip    # nécessite python >= 3.8
pip3 install -r utils/requirements.txt  # vous devez d'abord cloner ce dépôt

# ajouter la cible WASM
rustup target add wasm32-unknown-unknown

# installer d'autres composants
sudo apt install figlet
cargo install rustfilt

# [optionnel] outils utiles pour le développement
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### Configuration pour macOS

Les commandes suivantes sont pour les utilisateurs de macOS, elles n'ont été testées que sur un Mac avec puce Apple Silicon, donc à utiliser avec prudence.

```bash
# installer Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# installer LLVM 15
brew install llvm@15

# installer les paquets Python
pip3 install -r utils/requirements.txt  # vous devez d'abord cloner ce dépôt
                                        # en utilisant python3 par défaut de macOS

# ajouter la cible WASM
rustup target add wasm32-unknown-unknown

# installer d'autres composants
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

Nous proposons une solution Docker.

```bash
# construire l'image
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# exécuter un conteneur à partir de l'image
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# exécuter le conteneur
docker start rustle
docker exec -it -w /rustle rustle bash
```

### Utilisation

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir` : Chemin vers la source du contrat.
* `tg_dir` : Chemin vers la cible de construction du contrat. Par défaut, il est identique à `src_dir`.
* `detector` : La liste des détecteurs. Elle peut être utilisée pour passer plusieurs *détecteurs* ou *groupes* séparés par `,`. Par défaut à `all`.
  *   passer `all` pour activer tous les détecteurs.
  *   passer `high`, `medium`, `low` et `info` pour activer les groupes de détecteurs avec différents niveaux de sévérité (voir [Détecteurs](#detectors))
  *   passer `nep-ft`, `nep-storage` et `nep-nft` pour activer les détecteurs implémentés pour les NEP spécifiés (voir [Groupes de détecteurs NEP](#nep-detector-groups))
  *   passer les identifiants de détecteurs dans le [tableau](#detectors) pour activer ces détecteurs
* `output` : Chemin où les rapports d'audit seront générés. Par défaut à `./audit-result`.

Note : si le code binaire cible (fichier `.bc`) construit par cargo n'est pas dans le répertoire `$src_dir`, utilisez `-t|--tg_dir` pour définir le répertoire cible, sinon il sera défini sur `$src_dir` par défaut.

La commande ci-dessous montre un exemple d'analyse de LiNEAR.

```bash
# cloner LiNEAR
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# exécuter Rustle
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [optionnel] exécuter Rustle sur des détecteurs spécifiés ou des groupes de sévérité et sauvegarder les rapports d'audit dans `~/linear-report`
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

Un rapport au format CSV sera généré dans le répertoire `./audit-result`.

## Détecteurs

Toutes les vulnérabilités que **Rustle** peut identifier.

|ID du détecteur|Description|Sévérité|
|---|---|---|
|`unhandled-promise`|trouver les `Promises` qui ne sont pas gérées|Élevé|
|`non-private-callback`|absence de la macro `#[private]` pour les fonctions de rappel|Élevé|
|`reentrancy`|identifier les fonctions vulnérables aux attaques de réentrance|Élevé|
|`unsafe-math`|absence de vérification de débordement pour les opérations arithmétiques|Élevé|
|`self-transfer`|absence de vérification `sender != receiver`|Élevé|
|`incorrect-json-type`|utilisation d'un type incorrect dans les paramètres ou les valeurs de retour|Élevé|
|`unsaved-changes`|les modifications apportées aux collections ne sont pas enregistrées|Élevé|
|`nft-approval-check`|identifier `nft_transfer` sans vérification de l'`approval id`|Élevé|
|`nft-owner-check`|identifier les fonctions d'approbation ou de révocation sans vérification du propriétaire|Élevé|
|`div-before-mul`|perte de précision due à un ordre d'opérations incorrect|Moyen|
|`round`|arrondissement sans spécifier `ceil` ou `floor`|Moyen|
|`lock-callback`|un `panic` dans une fonction de rappel peut verrouiller le contrat|Moyen|
|`yocto-attach`|absence de `assert_one_yocto` dans une fonction privilégiée|Moyen|
|`dup-collection-id`|utilisation d'un identifiant en double dans les collections|Moyen|
|`unregistered-receiver`|absence de `panic` pour les récepteurs de transfert non enregistrés|Moyen|
|`nep${id}-interface`|identifier toutes les interfaces NEP non implémentées|Moyen|
|`prepaid-gas`|absence de vérification du gaz prépayé dans `ft_transfer_call`|Faible|
|`non-callback-private`|utilisation de la macro `#[private]` dans une fonction non-callback|Faible|
|`unused-ret`|résultat de fonction non utilisé ou vérifié|Faible|
|`upgrade-func`|absence de fonction de mise à niveau dans le contrat|Faible|
|`tautology`|utilisation de tautologie dans une branche conditionnelle|Faible|
|`storage-gas`|absence de vérification du solde pour l'expansion du stockage|Faible|
|`unclaimed-storage-fee`|absence de vérification du solde avant désinscription du stockage|Faible|
|`inconsistency`|utilisation de symboles similaires mais légèrement différents|Info|
|`timestamp`|identifier toutes les utilisations de `timestamp`|Info|
|`complex-loop`|identifier toutes les boucles avec une logique complexe pouvant conduire à un DoS|Info|
|`ext-call`|identifier toutes les invocations inter-contrats|Info|
|`promise-result`|identifier toutes les utilisations de résultat de promesse|Info|
|`transfer`|identifier toutes les actions de transfert|Info|
|`public-interface`|identifier toutes les interfaces publiques|Info|

### Groupes de détecteurs NEP

En plus des groupes par niveau de sévérité, **Rustle** propose des groupes de détecteurs par NEP correspondant. Actuellement, **Rustle** prend en charge les groupes suivants.


|NEP|ID de groupe de détecteurs|ID des détecteurs|
|---|---|---|
|[NEP-141][nep141]|`nep-ft`|`nep141-interface`, `self-transfer`, `unregistered-receiver`|
|[NEP-145][nep145]|`nep-storage`|`nep145-interface`, `unclaimed-storage-fee`|
|[NEP-171][nep171], [NEP-178][nep178]|`nep-nft`|`nep171-interface`, `nft-approval-check`, `nft-owner-check`|

## Ajouter de nouveaux détecteurs

1. Forkez ce dépôt sur votre compte.
2. Placez le nouveau détecteur dans le dossier [/detectors](/detectors/).
3. Ajoutez une cible de détection dans le [/Makefile](/Makefile) avec des commandes pour exécuter votre détecteur.
4. Ajoutez la cible à la dépendance de la cible `audit` et son nom à la [liste des détecteurs](/rustle#L146) et aux [groupes de sévérité](/rustle#L169) dans le script `./rustle`.
5. Ajoutez le code de traitement dans [utils/audit.py](/utils/audit.py) (référez-vous au code des autres détecteurs dans `audit.py`).
6. Soumettez une pull request de votre branche vers la branche principale.

## Remarque

**Rustle** peut être utilisé dans le processus de développement pour analyser itérativement les contrats intelligents NEAR. Cela peut économiser beaucoup d'efforts manuels et atténuer certains problèmes potentiels. Cependant, les vulnérabilités liées à une logique complexe ou à la sémantique restent une limite pour **Rustle**. L'identification de problèmes sémantiques complexes nécessite que les experts de [BlockSec](https://blocksec.com/) effectuent des examens exhaustifs et approfondis. [Contactez-nous](audit@blocksec.com) pour un service d'audit.

## Licence

Ce projet est sous la licence AGPLv3. Consultez le fichier [LICENSE](LICENSE) pour le texte intégral de la licence.
