void HSVPixel::loadTo(RGBPixel *pix) {
      int i;
      float f, p, q, t;

      if ( saturation == 0 ) {
        // achromatic (grey)
        pix->red = pix->green = pix->blue = value;
        return;
      }

      hue /= 60;			// sector 0 to 5
      i = floor( hue );
      f = hue - i;			// factorial part of h
      p = value * ( 1 - saturation );
      q = value * ( 1 - saturation * f );
      t = value * ( 1 - saturation * ( 1 - f ) );

      switch ( i ) {
        case 0:
          pix->red = value;
          pix->green = t;
          pix->blue = p;
          break;
        case 1:
          pix->red = q;
          pix->green = value;
          pix->blue = p;
          break;
        case 2:
          pix->red = p;
          pix->green = value;
          pix->blue = t;
          break;
        case 3:
          pix->red = p;
          pix->green = q;
          pix->blue = value;
          break;
        case 4:
          pix->red = t;
          pix->green = p;
          pix->blue = value;
          break;
        default:		// case 5:
          pix->red = value;
          pix->green = p;
          pix->blue = q;
          break;
      }
    }
