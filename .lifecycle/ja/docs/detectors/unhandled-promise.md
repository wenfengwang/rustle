
## 未処理のプロミスの結果

### 設定

* 検出器ID: `unhandled-promise`
* 重大度: 高

### 説明

プロミスの結果は、常にコールバック関数または別のプロミスで処理されるべきです。スマートコントラクトでプロミスを未処理のままにすることは推奨されません。そうしないと、プロミスが失敗した場合に、変更された状態をロールバックすることができなくなります。

### サンプルコード

```rust
token.ft_transfer_call(receiver, U128(amount), None, "".to_string());
```

このサンプルでは、コントラクトは `ft_transfer_call` を呼び出しますが、指定されたコールバック関数（例えば `resolve_transfer`）でそのプロミスの結果を処理していません。そのため、コントラクトは転送が成功したかどうかを知ることができません。そして、転送が失敗した場合、コントラクトの状態はロールバックされません。