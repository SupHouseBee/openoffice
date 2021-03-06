/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.lang.XMultiComponentFactory;
import com.sun.star.beans.XPropertySet;
import com.sun.star.beans.PropertyValue;
import com.sun.star.beans.UnknownPropertyException;

/*
 *
 * @author  Carsten Driesner
 * Provides example code how to access and use the
 * path pathsettings servce.
 */
public class PathSettingsTest extends java.lang.Object {
    
    /*
     * List of pre-defined path variables supported by
     * the path settings service.
     */
    private static String[] predefinedPathProperties = {
        "Addin",
        "AutoCorrect",
        "AutoText",
        "Backup",
        "Basic",
        "Bitmap",
        "Config",
        "Dictionary",
        "Favorite",
        "Filter",
        "Gallery",
        "Graphic",
        "Help",
        "Linguistic",
        "Module",
        "Palette",
        "Plugin",
        "Storage",
        "Temp",
        "Template",
        "UIConfig",
        "UserConfig",
        "UserDictionary",
        "Work"
    };
    
    /*
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        XComponentContext xRemoteContext = null;
        XMultiComponentFactory xRemoteServiceManager = null;
        XPropertySet xPathSettingsService = null;
        
        try {
            // get the remote office context. If necessary a new office
            // process is started
            xRemoteContext = com.sun.star.comp.helper.Bootstrap.bootstrap();
            System.out.println("Connected to a running office ...");
            xRemoteServiceManager = xRemoteContext.getServiceManager();
            
            Object pathSubst = xRemoteServiceManager.createInstanceWithContext(
                "com.sun.star.comp.framework.PathSettings", xRemoteContext );
            xPathSettingsService = (XPropertySet)UnoRuntime.queryInterface(
                XPropertySet.class, pathSubst);
            
            /* Work with path settings */
            workWithPathSettings( xPathSettingsService );
        }
        catch (java.lang.Exception e){
            e.printStackTrace();
        }
        finally {
            System.exit(0);
        }
    }

    /*
     * Retrieve and set path properties from path settings service
     * @param xPathSettingsService the path settings service
     */
    public static void workWithPathSettings( XPropertySet xPathSettingsService )
    {
        if ( xPathSettingsService != null ) {
            for ( int i=0; i<predefinedPathProperties.length; i++ ) {
                try {
                        /* Retrieve values for path properties from path settings
                         * service*/ 
                        Object aValue = xPathSettingsService.getPropertyValue( 
                                            predefinedPathProperties[i] );
                        
                        // getPropertyValue returns an Object, you have to cast
                        // it to type that you need 
                        String aPath = (String)aValue;
                        System.out.println( "Property="+ predefinedPathProperties[i]
                                            + " Path=" + aPath );
                }
                catch ( com.sun.star.beans.UnknownPropertyException e) {
                    System.err.println( "UnknownPropertyException has been thrown accessing "+predefinedPathProperties[i]);
                }
                catch ( com.sun.star.lang.WrappedTargetException e ) {
                    System.err.println( "WrappedTargetException has been thrown accessing "+predefinedPathProperties[i]);
                }
            }
            
            // Try to modfiy the work path property. After running this example
            // you should see the new value of "My Documents" in the path options 
            // tab page, accessible via "Tools - Options - [Star|Open]Office -
            // Paths". 
            // If you want to revert the changes, you can also do it with the
            // path tab page.
            try {
                xPathSettingsService.setPropertyValue( "Work", "$(temp)" );
                String aValue = (String)xPathSettingsService.getPropertyValue( "Work" );
                System.out.println( "\nNote: The example changes your current "
                                    +"setting of the work path!\nThe work path "
                                    +"should be now=" + aValue );
            }
            catch ( com.sun.star.beans.UnknownPropertyException e) {
                System.err.println( "UnknownPropertyException has been thrown accessing PathSettings service");
            }
            catch ( com.sun.star.lang.WrappedTargetException e ) {
                System.err.println( "WrappedTargetException has been thrown accessing PathSettings service");
            }
            catch ( com.sun.star.beans.PropertyVetoException e ) {
                System.err.println( "PropertyVetoException has been thrown accessing PathSettings service");
            }
            catch ( com.sun.star.lang.IllegalArgumentException e ) {
                System.err.println( "IllegalArgumentException has been thrown accessing PathSettings service");
            }
        }
    }
}
