package dev.trindadedev.brut;

import android.content.Context;
import android.content.res.AssetManager;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class BrutAssetsManager {
  private final AssetManager assetManager;
  private final String assetsRoot;

  public BrutAssetsManager(Context ctx, String root) {
    this.assetManager = ctx.getAssets();
    this.assetsRoot = root;
  }

  public String readTextFile(String path) {
    try {
      InputStream inputStream = assetManager.open(assetsRoot + path);
      BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
      StringBuilder content = new StringBuilder();
      String line;
      while ((line = reader.readLine()) != null) {
        content.append(line).append('\n');
      }
      return content.toString();
    } catch (IOException e) {
      e.printStackTrace();
    }
    return "";
  }

  public byte[] readBinaryFile(String path) {
    try {
      InputStream inputStream = assetManager.open(assetsRoot + path);
      int size = inputStream.available();
      byte[] buffer = new byte[size];
      int readBytes = inputStream.read(buffer);
      if (readBytes != size) {
        throw new IOException("Incomplete read");
      }
      return buffer;
    } catch (IOException e) {
      e.printStackTrace();
    }
    return new byte[0];
  }

  public boolean fileExists(String path) {
    try {
      final InputStream is = assetManager.open(assetsRoot + path);
      is.close();
      return true;
    } catch (IOException e) {
      e.printStackTrace();
    }
    return false;
  }

  public String[] listFiles(String path) {
    try {
      String[] files = assetManager.list(assetsRoot + path);
      if (files != null) {
        return files;
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
    return new String[0];
  }
}