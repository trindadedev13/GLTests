package dev.trindadedev.brut;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import org.libsdl.app.SDLActivity;

public final class BrutActivity extends SDLActivity implements BrutGamePadView.GamePadListener {
  private BrutAssetsManager asmg;
  private BrutGamePadView gpv;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    // Assets Manager JNI
    asmg = new BrutAssetsManager(
            /* context  = */ this,
            /* rootPath = */ "");
    initAssets(asmg);
    // Set game pad listener
    configureGamePad();
  }

  private final void configureGamePad() {
    gpv = new BrutGamePadView(this);

    final int gpvW = 300;
    final int gpvH = 300;

    final RelativeLayout.LayoutParams gpvParams = new RelativeLayout.LayoutParams(gpvW, gpvH);
    gpvParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
    gpvParams.addRule(RelativeLayout.ALIGN_PARENT_START);
    gpvParams.setMargins(32, 32, 32, 32);

    gpv.setLayoutParams(gpvParams);
    gpv.setGamePadListener(this);

    mLayout.addView(gpv);
  }

  @Override
  public void onPress(final int key) {
    onNativeKeyDown(key);
  }

  @Override
  public void onRelease(final int key) {
    onNativeKeyUp(key);
  }

  @Override
  public void onDoublePress(final int key) {
    // TODO
  }

  @Override
  public void onHold(final int key) {
    onNativeKeyDown(key);
  }

  @Override
  public void setOrientationBis(
          final int w, final int h, final boolean resizable, final String hint) {
    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
  }

  public static native void initAssets(final BrutAssetsManager assetsManager);
}
