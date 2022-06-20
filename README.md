# dx11w

## なにこれ
- DirectX11をラップしたもの

## 環境構築
- Windows10 64bit
- DirectX SDK June 2010
- Visual Studio 2022 Community

## 環境構築(拡張機能用)
- DirectXTK
    - 2022/06/10現在のmainブランチを使用
    - pch.hのwincodec.h手前にd2d1.hをインクルード
    - `DirectXTK_Desktop_2022` を使用
    - ビルド完了後はlibディレクトリにlibファイルを格納
        - debug / release版の仕分けとして、DirectXTKd.lib / DirectXTK.libで管理
