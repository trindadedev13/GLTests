package dev.trindadedev.brut;

import android.os.Bundle;
import org.libsdl.app.SDLActivity;

public class BrutActivity extends SDLActivity {

  private BrutAssetsManager asmg;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    asmg = new BrutAssetsManager(
       /* context  = */ this,
       /* rootPath = */ "");
    initAssets(asmg);
  }

  public static native void initAssets(final BrutAssetsManager assetsManager);
}
