
# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustleは、Rustで書かれたNEARスマートコントラクトの自動静的解析ツールです。NEARスマートコントラクトに存在する様々な脆弱性を特定するのに役立ちます。
[DefiLlama](https://defillama.com/chain/Near)によると、NEAR上のトップ10DAppsのうち8つがBlockSecによって監査されています。豊富な監査経験とNEARプロトコルに対する深い理解を持つ私たちは、このツールを開発しコミュニティに提供しています。

## はじめに

### 前提条件

#### Linuxのセットアップ

Linuxで**Rustle**に必要なツールキットをインストールするには、以下のコマンドをUbuntu 20.04 LTSで実行します。

```bash
# Rust Toolchainをインストール
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15をインストール
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# Pythonツールチェーンをインストール
sudo apt install python3 python3-pip    # requires python >= 3.8
pip3 install -r utils/requirements.txt  # まずこのリポジトリをクローンする必要があります

# WASMターゲットを追加
rustup target add wasm32-unknown-unknown

# その他のコンポーネントをインストール
sudo apt install figlet
cargo install rustfilt

# [オプション] 開発に役立つツール
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOSのセットアップ

以下のコマンドはmacOSユーザー向けですが、Apple Silicon Macでのみテストされているため、注意して使用してください。

```bash
# Rust Toolchainをインストール
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15をインストール
brew install llvm@15

# Pythonパッケージをインストール
pip3 install -r utils/requirements.txt  # まずこのリポジトリをクローンする必要があります
                                        # macOSのデフォルトpython3を使用

# WASMターゲットを追加
rustup target add wasm32-unknown-unknown

# その他のコンポーネントをインストール
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

Dockerソリューションを提供しています。

```bash
# イメージをビルド
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# イメージからコンテナを実行
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# コンテナを実行
docker start rustle
docker exec -it -w /rustle rustle bash
```

### 使用方法

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`: コントラクトソースへのパス。
* `tg_dir`: コントラクトビルドターゲットへのパス。デフォルトでは`src_dir`と同じです。
* `detector`: 検出器リスト。複数の*検出器*または*グループ*を`,`で区切って指定できます。デフォルトは`all`です。
  *   すべての検出器を有効にするには、`all` *グループ*を指定します。
  *   `high`、`medium`、`low`、`info` *グループ*を指定して、異なる重大度の検出器グループを有効にします（[検出器](#detectors)を参照）
  *   特定のNEPに対して実装された検出器を有効にするために、`nep-ft`、`nep-storage`、`nep-nft` *グループ*を指定します（[NEP検出器グループ](#nep-detector-groups)を参照）
  *   [テーブル](#detectors)にある*検出器ID*を指定して、それらの検出器を有効にします
* `output`: 監査レポートが生成されるパス。デフォルトは`./audit-result`です。

注: ターゲットビットコード（`.bc`バイナリ）が`$src_dir`にない場合は、`-t|--tg_dir`を使用してターゲットディレクトリを設定するか、デフォルトで`$src_dir`に設定されます。

以下のコマンドは、LiNEARの解析例を示しています。

```bash
# LiNEARをクローン
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# Rustleを実行
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [オプション] 特定の検出器または重大度グループでRustleを実行し、監査レポートを`~/linear-report`に保存
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```


# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustleは、Rustで書かれたNEARスマートコントラクトの自動静的解析ツールです。NEARスマートコントラクトの数十種類の脆弱性を特定するのに役立ちます。
[DefiLlama](https://defillama.com/chain/Near)によると、NEARのトップ10 DAppsのうち8つがBlockSecによって監査されています。豊富な監査経験とNEARプロトコルに対する深い理解を持って、私たちはこのツールを構築し、コミュニティと共有します。

## はじめに

### 前提条件

#### Linuxのセットアップ

以下のコマンドを使用して、Linuxの**Rustle**に必要なツールキットをインストールします。コマンドはUbuntu 20.04 LTSでテストされています。

```bash
# Rust Toolchainをインストール
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15をインストール
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# Pythonツールチェーンをインストール
sudo apt install python3 python3-pip    # python >= 3.8が必要です
pip3 install -r utils/requirements.txt  # このリポジトリを先にクローンする必要があります

# WASMターゲットを追加
rustup target add wasm32-unknown-unknown

# その他のコンポーネントをインストール
sudo apt install figlet
cargo install rustfilt

# [オプション] 開発用の便利なツール
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOSのセットアップ

以下のコマンドはmacOSユーザー向けですが、Apple Silicon Macでのみテストされているので注意して使用してください。

```bash
# Rust Toolchainをインストール
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# LLVM 15をインストール
brew install llvm@15

# Pythonパッケージをインストール
pip3 install -r utils/requirements.txt  # このリポジトリを先にクローンする必要があります
                                        # macOSのデフォルトpython3を使用

# WASMターゲットを追加
rustup target add wasm32-unknown-unknown

# その他のコンポーネントをインストール
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

Dockerソリューションを提供しています。

```bash
# イメージをビルド
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# イメージからコンテナを実行
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# コンテナを実行
docker start rustle
docker exec -it -w /rustle rustle bash
```

### 使用法

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`: コントラクトソースへのパス。
* `tg_dir`: コントラクトビルドターゲットへのパス。デフォルトは`src_dir`と同じです。
* `detector`: 検出器リスト。`,`で区切られた複数の*検出器*または*グループ*を渡すために使用できます。デフォルトは`all`です。
  *   すべての検出器を有効にするには、*グループ* `all`を渡します。
  *   異なる重大度の検出器グループを有効にするには、*グループ* `high`, `medium`, `low`, `info`を渡します（[Detectors](#detectors)を参照）。
  *   指定されたNEP用に実装された検出器を有効にするには、*グループ* `nep-ft`, `nep-storage`, `nep-nft`を渡します（[NEP検出器グループ](#nep-detector-groups)を参照）。
  *   [表](#detectors)にある*検出器ID*を渡して、それらの検出器を有効にします。
* `output`: 監査レポートが生成されるパス。デフォルトは`./audit-result`です。

注: cargoによってビルドされたターゲットビットコード（`.bc`バイナリ）が`$src_dir`にない場合は、`-t|--tg_dir`を使用してターゲットのディレクトリを設定するか、デフォルトで`$src_dir`に設定されます。

以下のコマンドは、LiNEARの分析の例を示しています。

```bash
# LiNEARをクローン
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# Rustleを実行
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [オプション] 指定された検出器または重大度グループでRustleを実行し、監査レポートを`~/linear-report`に保存
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

CSV形式のレポートがディレクトリ「./audit-result」に生成されます。

## Detectors

**Rustle**が発見できるすべての脆弱性。

|Detector ID|説明|重大度|
|---|---|---|
|`unhandled-promise`|処理されていない`Promise`を検索|High|
|`non-private-callback`|コールバック関数のマクロ`#[private]`がありません|High|
|`reentrancy`|リエントランシー攻撃に対して脆弱な関数を見つける|High|
|`unsafe-math`|算術演算のオーバーフローチェックが欠如|High|
|`self-transfer`|送信者と受信者が同じである場合のチェックがありません|High|
|`incorrect-json-type`|パラメータまたは戻り値で使用されている型が間違っています|High|
|`unsaved-changes`|コレクションへの変更が保存されていません|High|
|`nft-approval-check`|承認IDのチェックなしで`nft_transfer`を検索|High|
|`nft-owner-check`|所有者チェックなしで承認または取り消し関数を検索|High|
|`div-before-mul`|不正な演算順序による精度の損失|Medium|
|`round`|天井または床を指定せずに丸める|Medium|
|`lock-callback`|コールバック関数内のパニックによりコントラクトがロックされる可能性があります|Medium|
|`yocto-attach`|特権関数に`assert_one_yocto`がありません|Medium|
|`dup-collection-id`|コレクションで重複したIDが使用されています|Medium|
|`unregistered-receiver`|未登録の転送受信者でパニックが発生しない|Medium|
|`nep${id}-interface`|すべての未実装のNEPインターフェイスを検索|Medium|
|`prepaid-gas`|`ft_transfer_call`でプリペイドガスのチェックがありません|Low|
|`non-callback-private`|非コールバック関数で使用されるマクロ`#[private]`|Low|
|`unused-ret`|関数の結果が使用されていないか、チェックされていません|Low|
|`upgrade-func`|契約にアップグレード機能がありません|Low|
|`tautology`|条件分岐で使用されるトートロジー|Low|
|`storage-gas`|ストレージ拡張のバランスチェックがありません|Low|
|`unclaimed-storage-fee`|ストレージ登録解除前の残高チェックが欠落|Low|
|`inconsistency`|似ているがわずかに異なるシンボルの使用|Info|
|`timestamp`|`timestamp`のすべての使用法を検索|Info|
|`complex-loop`|DoSにつながる可能性のある複雑なロジックを含むすべてのループを検索|Info|
|`ext-call`|すべてのクロスコントラクト呼び出しを検索|Info|
|`promise-result`|promise resultのすべての使用法を検索|Info|
|`transfer`|すべての転送アクションを検索|Info|
|`public-interface`|すべてのパブリックインターフェイスを検索|Info|

### NEP検出器グループ

重大度レベルによるグループとは別に、**Rustle**は対応するNEPによるいくつかの検出器グループを提供しています。現在、**Rustle**は以下のグループをサポートしています。

|NEP|Detector Group ID|Detector IDs|
|---|---|---|
|[NEP-141][nep141]|`nep-ft`|`nep141-interface`, `self-transfer`, `unregistered-receiver`|
|[NEP-145][nep145]|`nep-storage`|`nep145-interface`, `unclaimed-storage-fee`|
|[NEP-171][nep171], [NEP-178][nep178]|`nep-nft`|`nep171-interface`, `nft-approval-check`, `nft-owner-check`|

## 新しい検出器を追加する

1. このリポジトリをあなたのアカウントにフォークします。
2. 新しいディテクタを[/detectors](/detectors/)の下に配置します。
3. [/Makefile](/Makefile)に検出対象を追加し、ディテクタを実行するコマンドを記述します。
4. `audit`ターゲットの依存関係にターゲットを追加し、`./rustle`スクリプトの[検出器リスト](/rustle#L146)と[重大度グループ](/rustle#L169)にその名前を追加します。
5. [utils/audit.py](/utils/audit.py)に処理コードを追加します（`audit.py`内の他のディテクタのコードを参照してください）。
6. あなたのブランチからメインブランチへプルリクエストを送信します。

## 注意

**Rustle**は開発プロセス中にNEARスマートコントラクトを反復的にスキャンするために使用できます。これにより、多くの手作業を節約し、潜在的な問題の一部を軽減することができます。しかし、複雑なロジックやセマンティクスに関連する脆弱性は、**Rustle**の限界です。複雑なセマンティックな問題の特定には、[BlockSec](https://blocksec.com/)の専門家が徹底的かつ綿密なレビューを行う必要があります。監査サービスについては[お問い合わせください](audit@blocksec.com)。

## ライセンス

このプロジェクトはAGPLv3ライセンスの下にあります。完全なライセンステキストについては、[LICENSE](LICENSE)ファイルをご覧ください。

**Rustle**は開発プロセス中にNEARスマートコントラクトを反復的にスキャンするために使用できます。これにより、多くの手動作業を削減し、潜在的な問題の一部を軽減することができます。しかし、複雑なロジックやセマンティクスに関連する脆弱性は、依然として**Rustle**の限界です。複雑なセマンティックな問題の特定には、[BlockSec](https://blocksec.com/)の専門家が徹底的かつ綿密なレビューを行う必要があります。監査サービスについては、[お問い合わせ](audit@blocksec.com)ください。

## ライセンス

このプロジェクトはAGPLv3ライセンスの下で提供されています。ライセンスの全文については、[LICENSE](LICENSE)ファイルをご覧ください。
