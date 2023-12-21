
## コールバック関数に `#[private]` マクロがない

### Configuration

* detector id: `non-private-callback`
* severity: 高

### Description

コールバック関数は `#[private]` でデコレートされるべきです。これにより、コントラクト自身によってのみ呼び出すことができるようになります。

このマクロがなければ、誰でもコールバック関数を呼び出すことが可能になり、これは元の設計に反しています。

### サンプルコード

```rust
pub fn callback_stake(&mut self) { // これはコールバック関数です
    // ...
}
```

関数 `callback_stake` は `#[private]` でデコレートされるべきです：

```rust
#[private]
pub fn callback_stake(&mut self) { // これはコールバック関数です
    // ...
}
```

このマクロを使用すると、コントラクト自体のみが `callback_stake` を呼び出すことができます。
