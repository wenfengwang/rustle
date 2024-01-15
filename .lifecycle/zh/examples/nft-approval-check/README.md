# `nft-approval-check` 检测器示例

此示例基于[near合约标准](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs)的实现。然而，它新增了一个函数[`internal_transfer_unsafe`](src/lib.rs#L256)。在这个函数中，移除了`approval_id`的检查，这是不正确的。

接口 `nft_transfer` 将调用这个新的不安全的 `internal_transfer_unsafe`，而 `nft_transfer_call` 仍将使用安全的 `internal_transfer`。因此，**Rustle** 将会把 `nft_transfer` 标记为不安全的。