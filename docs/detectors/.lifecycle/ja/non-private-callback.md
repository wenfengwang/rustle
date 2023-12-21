
## コールバック関数に `#[private]` マクロがない問題

### Configuration

* detector id: `non-private-callback`
* severity: 高

### Description

コールバック関数は `#[private]` で装飾されるべきです。これにより、コントラクト自身によってのみ呼び出されることが保証されます。

このマクロがなければ、誰でもコールバック関数を呼び出すことが可能となり、これは元の設計に反する行為です。

### サンプルコード

```rust
pub fn callback_stake(&mut self) { // これはコールバック関数です
    // ...
}
```

関数 `callback_stake` は `#[private]` で装飾されるべきです：

```rust
#[private]
pub fn callback_stake(&mut self) { // これはコールバック関数です
    // ...
}
```

このマクロを使用すると、`callback_stake` はコントラクト自身によってのみ呼び出されます。
